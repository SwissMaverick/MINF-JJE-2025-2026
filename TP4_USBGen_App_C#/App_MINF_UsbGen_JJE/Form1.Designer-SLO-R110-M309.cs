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
            this.gbCom.Controls.Add(this.btnConnecter);
            this.gbCom.Controls.Add(this.cmbPorts);
            this.gbCom.Location = new System.Drawing.Point(12, 12);
            this.gbCom.Name = "gbCom";
            this.gbCom.Size = new System.Drawing.Size(515, 70);
            this.gbCom.TabIndex = 20;
            this.gbCom.TabStop = false;
            this.gbCom.Text = "Réglages communication";
            // 
            // btnConnecter
            // 
            this.btnConnecter.Location = new System.Drawing.Point(16, 30);
            this.btnConnecter.Name = "btnConnecter";
            this.btnConnecter.Size = new System.Drawing.Size(75, 23);
            this.btnConnecter.TabIndex = 19;
            this.btnConnecter.Text = "Open";
            this.btnConnecter.UseVisualStyleBackColor = true;
            this.btnConnecter.Click += new System.EventHandler(this.btOpenClose_Click);
            // 
            // cmbPorts
            // 
            this.cmbPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPorts.FormattingEnabled = true;
            this.cmbPorts.Location = new System.Drawing.Point(114, 32);
            this.cmbPorts.Margin = new System.Windows.Forms.Padding(2);
            this.cmbPorts.Name = "cmbPorts";
            this.cmbPorts.Size = new System.Drawing.Size(98, 21);
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
            this.cmbFormeSignal.Location = new System.Drawing.Point(16, 74);
            this.cmbFormeSignal.Name = "cmbFormeSignal";
            this.cmbFormeSignal.Size = new System.Drawing.Size(121, 21);
            this.cmbFormeSignal.TabIndex = 23;
            // 
            // numFrequence
            // 
            this.numFrequence.Increment = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numFrequence.Location = new System.Drawing.Point(17, 101);
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
            this.numFrequence.Size = new System.Drawing.Size(120, 20);
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
            this.numAmplitude.Location = new System.Drawing.Point(17, 127);
            this.numAmplitude.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numAmplitude.Name = "numAmplitude";
            this.numAmplitude.Size = new System.Drawing.Size(120, 20);
            this.numAmplitude.TabIndex = 25;
            // 
            // numOffset
            // 
            this.numOffset.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numOffset.Location = new System.Drawing.Point(17, 153);
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
            this.numOffset.Size = new System.Drawing.Size(120, 20);
            this.numOffset.TabIndex = 26;
            // 
            // btnSauvegarde
            // 
            this.btnSauvegarde.Location = new System.Drawing.Point(554, 24);
            this.btnSauvegarde.Name = "btnSauvegarde";
            this.btnSauvegarde.Size = new System.Drawing.Size(159, 23);
            this.btnSauvegarde.TabIndex = 20;
            this.btnSauvegarde.Text = "Sauvegarder en EEPROM";
            this.btnSauvegarde.UseVisualStyleBackColor = true;
            // 
            // labelForme
            // 
            this.labelForme.AutoSize = true;
            this.labelForme.Location = new System.Drawing.Point(143, 77);
            this.labelForme.Name = "labelForme";
            this.labelForme.Size = new System.Drawing.Size(80, 13);
            this.labelForme.TabIndex = 29;
            this.labelForme.Text = "Choix de Forme";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(143, 103);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 13);
            this.label1.TabIndex = 30;
            this.label1.Text = "Fréquence";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(143, 129);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 31;
            this.label4.Text = "Amplitude";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(143, 155);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 13);
            this.label7.TabIndex = 32;
            this.label7.Text = "Offset";
            // 
            // lstDataIn
            // 
            this.lstDataIn.FormattingEnabled = true;
            this.lstDataIn.Location = new System.Drawing.Point(19, 188);
            this.lstDataIn.Margin = new System.Windows.Forms.Padding(2);
            this.lstDataIn.Name = "lstDataIn";
            this.lstDataIn.Size = new System.Drawing.Size(221, 134);
            this.lstDataIn.TabIndex = 52;
            // 
            // lstDataOut
            // 
            this.lstDataOut.FormattingEnabled = true;
            this.lstDataOut.Location = new System.Drawing.Point(5, 188);
            this.lstDataOut.Margin = new System.Windows.Forms.Padding(2);
            this.lstDataOut.Name = "lstDataOut";
            this.lstDataOut.Size = new System.Drawing.Size(221, 134);
            this.lstDataOut.TabIndex = 56;
            // 
            // btSend
            // 
            this.btSend.Location = new System.Drawing.Point(197, 30);
            this.btSend.Name = "btSend";
            this.btSend.Size = new System.Drawing.Size(100, 23);
            this.btSend.TabIndex = 53;
            this.btSend.Text = "Envoi";
            this.btSend.UseVisualStyleBackColor = true;
            // 
            // gbRx
            // 
            this.gbRx.Controls.Add(this.lstDataIn);
            this.gbRx.Enabled = false;
            this.gbRx.Location = new System.Drawing.Point(390, 89);
            this.gbRx.Name = "gbRx";
            this.gbRx.Size = new System.Drawing.Size(374, 338);
            this.gbRx.TabIndex = 22;
            this.gbRx.TabStop = false;
            this.gbRx.Text = "RX";
            // 
            // gbTx
            // 
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
            this.gbTx.Location = new System.Drawing.Point(12, 89);
            this.gbTx.Name = "gbTx";
            this.gbTx.Size = new System.Drawing.Size(372, 338);
            this.gbTx.TabIndex = 21;
            this.gbTx.TabStop = false;
            this.gbTx.Text = "TX";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(776, 439);
            this.Controls.Add(this.btnSauvegarde);
            this.Controls.Add(this.gbRx);
            this.Controls.Add(this.gbTx);
            this.Controls.Add(this.gbCom);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.Name = "Form1";
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
    }
}

