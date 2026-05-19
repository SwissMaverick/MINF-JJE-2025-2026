// *************************************************
//
// Form1.cs
//
// Appli CS de pilotage du TP2 MINF
//
// 13.03.2025 SCA@etml-es
//
// *************************************************


using System;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using MaterialSkin;
using MaterialSkin.Controls;

namespace AppCsTp2Pwm
{
    public partial class Form1 : MaterialForm
    {
        private string _bufferReception = string.Empty;

        public delegate void ReceiverD();
        public ReceiverD myDelegate;

        public Form1()
        {
            InitializeComponent();

            // --- CONFIGURATION MATERIAL SKIN ---
            
            var materialSkinManager = MaterialSkinManager.Instance;
            materialSkinManager.AddFormToManage(this);
            materialSkinManager.Theme = MaterialSkinManager.Themes.LIGHT; // ou DARK si tu préfères le mode sombre !
            materialSkinManager.ColorScheme = new ColorScheme(
                Primary.BlueGrey800, Primary.BlueGrey900,
                Primary.BlueGrey500, Accent.LightBlue200,
                TextShade.WHITE);
            // -----------------------------------

            // Récupère la liste des ports COM disponibles
            string[] ports = SerialPort.GetPortNames();
            cmbPorts.Items.AddRange(ports);
            if (cmbPorts.Items.Count > 0) cmbPorts.SelectedIndex = 0;

            lstDataIn.Items.Clear();

            //pour réception
            myDelegate = new ReceiverD(DispInListRxData);

            if (cmbFormeSignal.Items.Count > 0)
            {
                cmbFormeSignal.SelectedIndex = 0; // Sélectionne automatiquement le 1er élément
            }
        }

        private void EnvoyerParametres(int demandeSauvegarde)
        {
            if (serialPort1.IsOpen)
            {
                if (cmbFormeSignal.SelectedItem == null)
                {
                    MessageBox.Show("Veuillez d'abord choisir une forme de signal !", "Attention", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return; // On arrête la fonction ici pour éviter le plantage
                }

                // 1. Récupération des valeurs (vérifie que les noms correspondent à ton interface)
                string forme = cmbFormeSignal.SelectedItem.ToString();
                string codeForme = forme.Substring(0, 1).ToUpper();
                if (forme == "DentDeScie") codeForme = "D"; // D pour DentDeScie [cite: 106]

                int freq = (int)numFrequence.Value;
                int amp = (int)numAmplitude.Value;
                int off = (int)numOffset.Value;

                // 2. Construction de la chaîne. {off:+#;-#;0} force le + pour les positifs 
                string message = $"!S={codeForme}F={freq}A={amp}O={off:+#;-#;0}W={demandeSauvegarde}#";

                // 3. Envoi et affichage
                try
                {
                    serialPort1.Write(message);

                    lstDataOut.Items.Add("TX: " + message);
                    if (lstDataOut.Items.Count > 10)
                        lstDataOut.Items.RemoveAt(0);
                }
                catch (Exception)
                {
                    // ON COUPE LE TIMER EN CAS D'ERREUR POUR EVITER LE SPAM
                    if (timerEnvoiContinu != null && timerEnvoiContinu.Enabled)
                    {
                        timerEnvoiContinu.Stop();
                        btnEnvoiContinu.Text = "Activer Envoi Continu";
                    }

                    MessageBox.Show("Erreur à l'émission !", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Le port n'est pas ouvert !", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }


        private void btOpenClose_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)    //ouverture du port
            {
                // Configuration du port
                serialPort1.PortName = (string)cmbPorts.SelectedItem;
                serialPort1.BaudRate  = 9600;
                serialPort1.Parity    = Parity.None;
                serialPort1.DataBits  = 8;
                serialPort1.StopBits  = StopBits.One;
                serialPort1.Handshake = Handshake.None;
                serialPort1.ReceivedBytesThreshold = 1;

                // Set the read/write timeouts
                serialPort1.ReadTimeout = 100;
                serialPort1.WriteTimeout = 100;

                try
                {
                    serialPort1.Open();

                    btnConnecter.Text = "Close";
                    gbTx.Enabled = true;
                    gbRx.Enabled = true;
                    cmbPorts.Enabled = false;
                }
                catch (Exception)
                {
                    MessageBox.Show("Erreur à l'ouverture du port !", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else //fermeture
            {
                serialPort1.Close();

                btnConnecter.Text = "Open";
                gbTx.Enabled = false;
                gbRx.Enabled = false;
                cmbPorts.Enabled = true;
                lstDataOut.Items.Clear();
                lstDataIn.Items.Clear();
            }
        } // end btOpenClose_Click

        //event datareceived du port série
        // Attention : avec certains types de port série, il arrive que cet event survienne
        //  alors qu'il n'y a aucune data reçue
        // De plus, cet event ne peut pas modifier des élement de la GUI (dans un thread différent)
        //  => utilisation d'un delegate qui s'exécute dans le thread de la GUI
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            lstDataIn.BeginInvoke(myDelegate); //utiliser BeginInvoke à la place (asynchrone)
        }

        //Delegate pour réception
        public void DispInListRxData()
        {
            try
            {
                // 1. On lit tout le texte qui vient d'arriver
                string donneesEntrantes = serialPort1.ReadExisting();
                _bufferReception += donneesEntrantes;

                // 2. On vérifie si la trame est complète (terminée par '#')
                if (_bufferReception.Contains("#"))
                {
                    // On affiche le message complet dans la liste
                    lstDataIn.Items.Add("RX: " + _bufferReception);

                    // Ne garde que les 10 dernières lignes
                    if (lstDataIn.Items.Count > 10)
                        lstDataIn.Items.RemoveAt(0);

                    // --- NOUVEAUTÉ : VÉRIFICATION DE LA SAUVEGARDE ---
                    // Si la trame reçue contient "WP=1", c'est que le PIC32 confirme la sauvegarde
                    if (_bufferReception.Contains("WP=1"))
                    {
                        MessageBox.Show("Sauvegarde en EEPROM réussie !", "Succès", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }

                    // 3. On vide le buffer pour le prochain message
                    _bufferReception = string.Empty;
                }
            }
            catch (Exception)
            {
                serialPort1.DiscardInBuffer();
                _bufferReception = string.Empty;
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Fermeture du port si nécessaire.
            // Workaround pour éviter blocage de l'app à la fermeture
            // Un simple appel à serialPort1.Close() fige l'app !
            try
            {
                serialPort1.Handshake = Handshake.None;
                serialPort1.DtrEnable = false;
                serialPort1.RtsEnable = false;
                serialPort1.DataReceived -= serialPort1_DataReceived;
                Thread.Sleep(200);
                if (serialPort1.IsOpen)
                {
                    serialPort1.DiscardInBuffer();
                    serialPort1.DiscardOutBuffer();
                    serialPort1.Close();
                }
            }
            catch (Exception)
            {
                //MessageBox.Show(ex.ToString(), "Erreur à la fermeture du port !", MessageBoxButtons.OK, MessageBoxIcon.Error);
                MessageBox.Show("Erreur à la fermeture du port !", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btSend_Click_1(object sender, EventArgs e)
        {
            EnvoyerParametres(0);
        }

        private void btnSauvegarde_Click(object sender, EventArgs e)
        {
            EnvoyerParametres(1);
        }

        private void btnEnvoiContinu_Click(object sender, EventArgs e)
        {
            // Si le timer est déjà en marche, on l'arrête
            if (timerEnvoiContinu.Enabled)
            {
                timerEnvoiContinu.Stop();
                btnEnvoiContinu.Text = "Activer Envoi Continu";
            }
            // Sinon, on le démarre (à condition que le port soit ouvert !)
            else
            {
                if (serialPort1.IsOpen)
                {
                    timerEnvoiContinu.Start();
                    btnEnvoiContinu.Text = "Stopper l'envoi";
                }
                else
                {
                    MessageBox.Show("Veuillez d'abord ouvrir le port COM !", "Attention", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        private void timerEnvoiContinu_Tick(object sender, EventArgs e)
        {
            // Par sécurité, si le port se ferme, on coupe le timer
            if (!serialPort1.IsOpen)
            {
                timerEnvoiContinu.Stop();
                btnEnvoiContinu.Text = "Activer Envoi Continu";
                return;
            }

            // On envoie la trame (0 = sans demande de sauvegarde en EEPROM)
            EnvoyerParametres(0);
        }
    }
}
