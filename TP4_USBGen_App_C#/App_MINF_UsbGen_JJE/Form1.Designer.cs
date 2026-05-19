namespace AppCsTp2Pwm
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.gbCom = new System.Windows.Forms.GroupBox();
            this.btnConnecter = new System.Windows.Forms.Button();
            this.cmbPorts = new System.Windows.Forms.ComboBox();
            this.cmbFormeSignal = new System.Windows.Forms.ComboBox();
            this.numFrequence = new System.Windows.Forms.NumericUpDown();
            this.numAmplitude = new System.Windows.Forms.NumericUpDown();
            this.numOffset = new System.Windows.Forms.NumericUpDown();
            this.btnSauvegarde = new System.Windows.Forms.Button();
            this.labelForme = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.lstDataIn = new System.Windows.Forms.ListBox();
            this.lstDataOut = new System.Windows.Forms.ListBox();
            this.btSend = new System.Windows.Forms.Button();
            this.gbRx = new System.Windows.Forms.GroupBox();
            this.gbTx = new System.Windows.Forms.GroupBox();
            this.btnEnvoiContinu = new System.Windows.Forms.Button();
            this.timerEnvoiContinu = new System.Windows.Forms.Timer(this.components);
            this.gbCom.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numFrequence)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAmplitude)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numOffset)).BeginInit();
            this.gbRx.SuspendLayout();
            this.gbTx.SuspendLayout();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 19200;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // gbCom
            // 
            this.gbCom.BackColor = System.Drawing.Color.Transparent;
            this.gbCom.Controls.Add(this.btnConnecter);
            this.gbCom.Controls.Add(this.cmbPorts);
            this.gbCom.Location = new System.Drawing.Point(14, 76);
            this.gbCom.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.gbCom.Name = "gbCom";
            this.gbCom.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.gbCom.Size = new System.Drawing.Size(601, 81);
            this.gbCom.TabIndex = 20;
            this.gbCom.TabStop = false;
            this.gbCom.Text = "Réglages communication";
            // 
            // btnConnecter
            // 
            this.btnConnecter.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btnConnecter.Location = new System.Drawing.Point(19, 35);
            this.btnConnecter.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.btnConnecter.Name = "btnConnecter";
            this.btnConnecter.Size = new System.Drawing.Size(88, 27);
            this.btnConnecter.TabIndex = 19;
            this.btnConnecter.Text = "Open";
            this.btnConnecter.UseVisualStyleBackColor = true;
            this.btnConnecter.Click += new System.EventHandler(this.btOpenClose_Click);
            // 
            // cmbPorts
            // 
            this.cmbPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPorts.FormattingEnabled = true;
            this.cmbPorts.Location = new System.Drawing.Point(133, 37);
            this.cmbPorts.Margin = new System.Windows.Forms.Padding(2);
            this.cmbPorts.Name = "cmbPorts";
            this.cmbPorts.Size = new System.Drawing.Size(114, 23);
            this.cmbPorts.Sorted = true;
            this.cmbPorts.TabIndex = 17;
            // 
            // cmbFormeSignal
            // 
            this.cmbFormeSignal.AutoCompleteCustomSource.AddRange(new string[] {
            "Sinus",
            "Triangle",
            "Dent de Scie",
            "Carré"});
            this.cmbFormeSignal.FormattingEnabled = true;
            this.cmbFormeSignal.Items.AddRange(new object[] {
            "Sinus",
            "Triangle",
            "Dent de Scie",
            "Carré"});
            this.cmbFormeSignal.Location = new System.Drawing.Point(294, 75);
            this.cmbFormeSignal.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.cmbFormeSignal.Name = "cmbFormeSignal";
            this.cmbFormeSignal.Size = new System.Drawing.Size(140, 23);
            this.cmbFormeSignal.TabIndex = 23;
            // 
            // numFrequence
            // 
            this.numFrequence.Increment = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numFrequence.Location = new System.Drawing.Point(294, 106);
            this.numFrequence.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.numFrequence.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.numFrequence.Minimum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numFrequence.Name = "numFrequence";
            this.numFrequence.Size = new System.Drawing.Size(140, 23);
            this.numFrequence.TabIndex = 24;
            this.numFrequence.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            // 
            // numAmplitude
            // 
            this.numAmplitude.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numAmplitude.Location = new System.Drawing.Point(294, 136);
            this.numAmplitude.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.numAmplitude.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numAmplitude.Name = "numAmplitude";
            this.numAmplitude.Size = new System.Drawing.Size(140, 23);
            this.numAmplitude.TabIndex = 25;
            // 
            // numOffset
            // 
            this.numOffset.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numOffset.Location = new System.Drawing.Point(294, 166);
            this.numOffset.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.numOffset.Maximum = new decimal(new int[] {
            5000,
            0,
            0,
            0});
            this.numOffset.Minimum = new decimal(new int[] {
            5000,
            0,
            0,
            -2147483648});
            this.numOffset.Name = "numOffset";
            this.numOffset.Size = new System.Drawing.Size(140, 23);
            this.numOffset.TabIndex = 26;
            // 
            // btnSauvegarde
            // 
            this.btnSauvegarde.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btnSauvegarde.Location = new System.Drawing.Point(22, 106);
            this.btnSauvegarde.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.btnSauvegarde.Name = "btnSauvegarde";
            this.btnSauvegarde.Size = new System.Drawing.Size(114, 68);
            this.btnSauvegarde.TabIndex = 20;
            this.btnSauvegarde.Text = "Sauvegarder en EEPROM";
            this.btnSauvegarde.UseVisualStyleBackColor = true;
            this.btnSauvegarde.Click += new System.EventHandler(this.btnSauvegarde_Click);
            // 
            // labelForme
            // 
            this.labelForme.AutoSize = true;
            this.labelForme.Location = new System.Drawing.Point(182, 78);
            this.labelForme.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelForme.Name = "labelForme";
            this.labelForme.Size = new System.Drawing.Size(91, 15);
            this.labelForme.TabIndex = 29;
            this.labelForme.Text = "Choix de Forme";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(211, 108);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 15);
            this.label1.TabIndex = 30;
            this.label1.Text = "Fréquence";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(211, 138);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 15);
            this.label4.TabIndex = 31;
            this.label4.Text = "Amplitude";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(234, 168);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(39, 15);
            this.label7.TabIndex = 32;
            this.label7.Text = "Offset";
            // 
            // lstDataIn
            // 
            this.lstDataIn.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lstDataIn.FormattingEnabled = true;
            this.lstDataIn.ItemHeight = 15;
            this.lstDataIn.Location = new System.Drawing.Point(22, 202);
            this.lstDataIn.Margin = new System.Windows.Forms.Padding(2);
            this.lstDataIn.Name = "lstDataIn";
            this.lstDataIn.Size = new System.Drawing.Size(446, 244);
            this.lstDataIn.TabIndex = 52;
            // 
            // lstDataOut
            // 
            this.lstDataOut.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lstDataOut.FormattingEnabled = true;
            this.lstDataOut.ItemHeight = 15;
            this.lstDataOut.Location = new System.Drawing.Point(19, 202);
            this.lstDataOut.Margin = new System.Windows.Forms.Padding(2);
            this.lstDataOut.Name = "lstDataOut";
            this.lstDataOut.Size = new System.Drawing.Size(453, 244);
            this.lstDataOut.TabIndex = 56;
            // 
            // btSend
            // 
            this.btSend.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btSend.Location = new System.Drawing.Point(84, 22);
            this.btSend.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.btSend.Name = "btSend";
            this.btSend.Size = new System.Drawing.Size(117, 27);
            this.btSend.TabIndex = 53;
            this.btSend.Text = "Envoi";
            this.btSend.UseVisualStyleBackColor = true;
            this.btSend.Click += new System.EventHandler(this.btSend_Click_1);
            // 
            // gbRx
            // 
            this.gbRx.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gbRx.BackColor = System.Drawing.Color.Transparent;
            this.gbRx.Controls.Add(this.lstDataIn);
            this.gbRx.Enabled = false;
            this.gbRx.Location = new System.Drawing.Point(537, 163);
            this.gbRx.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.gbRx.Name = "gbRx";
            this.gbRx.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.gbRx.Size = new System.Drawing.Size(490, 512);
            this.gbRx.TabIndex = 22;
            this.gbRx.TabStop = false;
            this.gbRx.Text = "RX";
            // 
            // gbTx
            // 
            this.gbTx.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gbTx.BackColor = System.Drawing.Color.Transparent;
            this.gbTx.Controls.Add(this.btnEnvoiContinu);
            this.gbTx.Controls.Add(this.btnSauvegarde);
            this.gbTx.Controls.Add(this.label7);
            this.gbTx.Controls.Add(this.btSend);
            this.gbTx.Controls.Add(this.label4);
            this.gbTx.Controls.Add(this.lstDataOut);
            this.gbTx.Controls.Add(this.label1);
            this.gbTx.Controls.Add(this.cmbFormeSignal);
            this.gbTx.Controls.Add(this.labelForme);
            this.gbTx.Controls.Add(this.numFrequence);
            this.gbTx.Controls.Add(this.numAmplitude);
            this.gbTx.Controls.Add(this.numOffset);
            this.gbTx.Enabled = false;
            this.gbTx.Location = new System.Drawing.Point(14, 163);
            this.gbTx.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.gbTx.Name = "gbTx";
            this.gbTx.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.gbTx.Size = new System.Drawing.Size(490, 512);
            this.gbTx.TabIndex = 21;
            this.gbTx.TabStop = false;
            this.gbTx.Text = "TX";
            // 
            // btnEnvoiContinu
            // 
            this.btnEnvoiContinu.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btnEnvoiContinu.Location = new System.Drawing.Point(294, 22);
            this.btnEnvoiContinu.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.btnEnvoiContinu.Name = "btnEnvoiContinu";
            this.btnEnvoiContinu.Size = new System.Drawing.Size(117, 27);
            this.btnEnvoiContinu.TabIndex = 57;
            this.btnEnvoiContinu.Text = "Envoi Continu";
            this.btnEnvoiContinu.UseVisualStyleBackColor = true;
            this.btnEnvoiContinu.Click += new System.EventHandler(this.btnEnvoiContinu_Click);
            // 
            // timerEnvoiContinu
            // 
            this.timerEnvoiContinu.Interval = 25;
            this.timerEnvoiContinu.Tick += new System.EventHandler(this.timerEnvoiContinu_Tick);
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1040, 686);
            this.Controls.Add(this.gbRx);
            this.Controls.Add(this.gbTx);
            this.Controls.Add(this.gbCom);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Padding = new System.Windows.Forms.Padding(0);
            this.Text = "App de test TP MINF PWM";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.gbCom.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numFrequence)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAmplitude)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numOffset)).EndInit();
            this.gbRx.ResumeLayout(false);
            this.gbTx.ResumeLayout(false);
            this.gbTx.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.GroupBox gbCom;
        private System.Windows.Forms.ComboBox cmbPorts;
        private System.Windows.Forms.Button btnConnecter;
        private System.Windows.Forms.ComboBox cmbFormeSignal;
        private System.Windows.Forms.NumericUpDown numFrequence;
        private System.Windows.Forms.NumericUpDown numAmplitude;
        private System.Windows.Forms.NumericUpDown numOffset;
        private System.Windows.Forms.Button btnSauvegarde;
        private System.Windows.Forms.Label labelForme;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ListBox lstDataIn;
        private System.Windows.Forms.ListBox lstDataOut;
        private System.Windows.Forms.Button btSend;
        private System.Windows.Forms.GroupBox gbRx;
        private System.Windows.Forms.GroupBox gbTx;
        private System.Windows.Forms.Button btnEnvoiContinu;
        private System.Windows.Forms.Timer timerEnvoiContinu;
    }
}

