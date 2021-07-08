namespace RobotControlApp
{
    partial class Form1
    {
        /// <summary>
        /// Wymagana zmienna projektanta.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Wyczyść wszystkie używane zasoby.
        /// </summary>
        /// <param name="disposing">prawda, jeżeli zarządzane zasoby powinny zostać zlikwidowane; Fałsz w przeciwnym wypadku.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kod generowany przez Projektanta formularzy systemu Windows

        /// <summary>
        /// Metoda wymagana do obsługi projektanta — nie należy modyfikować
        /// jej zawartości w edytorze kodu.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBoxParityBits = new System.Windows.Forms.ComboBox();
            this.comboBoxStopBits = new System.Windows.Forms.ComboBox();
            this.comboBoxDataBits = new System.Windows.Forms.ComboBox();
            this.comboBoxBaudRate = new System.Windows.Forms.ComboBox();
            this.comboBoxComPort = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.labelConnectionStatus = new System.Windows.Forms.Label();
            this.labelStatus = new System.Windows.Forms.Label();
            this.buttonCloseConnection = new System.Windows.Forms.Button();
            this.buttonOpenConnection = new System.Windows.Forms.Button();
            this.tabControlMode = new System.Windows.Forms.TabControl();
            this.tabPageAuto = new System.Windows.Forms.TabPage();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.pictureBoxLoad = new System.Windows.Forms.PictureBox();
            this.textBoxMap = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.labelRobotStatus = new System.Windows.Forms.Label();
            this.buttonAutonomousStart = new System.Windows.Forms.Button();
            this.tabPageRemote = new System.Windows.Forms.TabPage();
            this.groupBox13 = new System.Windows.Forms.GroupBox();
            this.groupBox12 = new System.Windows.Forms.GroupBox();
            this.buttonForward = new System.Windows.Forms.Button();
            this.buttonReverse = new System.Windows.Forms.Button();
            this.buttonLeft = new System.Windows.Forms.Button();
            this.buttonRight = new System.Windows.Forms.Button();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.labelDistance0 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.labelDistance1 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.labelDistance2 = new System.Windows.Forms.Label();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.labelDistance3 = new System.Windows.Forms.Label();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.labelAngle1 = new System.Windows.Forms.Label();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.labelAngle2 = new System.Windows.Forms.Label();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.textBoxtestowy = new System.Windows.Forms.TextBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tabControlMode.SuspendLayout();
            this.tabPageAuto.SuspendLayout();
            this.groupBox9.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLoad)).BeginInit();
            this.tabPageRemote.SuspendLayout();
            this.groupBox13.SuspendLayout();
            this.groupBox12.SuspendLayout();
            this.groupBox10.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox11.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.groupBox7.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.groupBox8.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.comboBoxParityBits);
            this.groupBox1.Controls.Add(this.comboBoxStopBits);
            this.groupBox1.Controls.Add(this.comboBoxDataBits);
            this.groupBox1.Controls.Add(this.comboBoxBaudRate);
            this.groupBox1.Controls.Add(this.comboBoxComPort);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(315, 219);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Ustawienia portu";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(19, 159);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(109, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "BITY PARZYSTOŚCI";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(19, 126);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "BITY STOPU";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "BITY";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(131, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "SZYBKOŚĆ TRANSMISJI";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(88, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "NUMER PORTU";
            // 
            // comboBoxParityBits
            // 
            this.comboBoxParityBits.FormattingEnabled = true;
            this.comboBoxParityBits.Items.AddRange(new object[] {
            "Brak",
            "Parzysty",
            "Nieprzaysty"});
            this.comboBoxParityBits.Location = new System.Drawing.Point(188, 153);
            this.comboBoxParityBits.Name = "comboBoxParityBits";
            this.comboBoxParityBits.Size = new System.Drawing.Size(121, 21);
            this.comboBoxParityBits.TabIndex = 4;
            this.comboBoxParityBits.Text = "Brak";
            // 
            // comboBoxStopBits
            // 
            this.comboBoxStopBits.FormattingEnabled = true;
            this.comboBoxStopBits.Items.AddRange(new object[] {
            "1",
            "2"});
            this.comboBoxStopBits.Location = new System.Drawing.Point(188, 118);
            this.comboBoxStopBits.Name = "comboBoxStopBits";
            this.comboBoxStopBits.Size = new System.Drawing.Size(121, 21);
            this.comboBoxStopBits.TabIndex = 3;
            this.comboBoxStopBits.Text = "1";
            // 
            // comboBoxDataBits
            // 
            this.comboBoxDataBits.FormattingEnabled = true;
            this.comboBoxDataBits.Items.AddRange(new object[] {
            "7",
            "8"});
            this.comboBoxDataBits.Location = new System.Drawing.Point(188, 83);
            this.comboBoxDataBits.Name = "comboBoxDataBits";
            this.comboBoxDataBits.Size = new System.Drawing.Size(121, 21);
            this.comboBoxDataBits.TabIndex = 2;
            this.comboBoxDataBits.Text = "8";
            // 
            // comboBoxBaudRate
            // 
            this.comboBoxBaudRate.FormattingEnabled = true;
            this.comboBoxBaudRate.Items.AddRange(new object[] {
            "75",
            "110",
            "300",
            "1200",
            "2400",
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200"});
            this.comboBoxBaudRate.Location = new System.Drawing.Point(188, 48);
            this.comboBoxBaudRate.Name = "comboBoxBaudRate";
            this.comboBoxBaudRate.Size = new System.Drawing.Size(121, 21);
            this.comboBoxBaudRate.TabIndex = 1;
            this.comboBoxBaudRate.Text = "9600";
            // 
            // comboBoxComPort
            // 
            this.comboBoxComPort.FormattingEnabled = true;
            this.comboBoxComPort.Location = new System.Drawing.Point(188, 13);
            this.comboBoxComPort.Name = "comboBoxComPort";
            this.comboBoxComPort.Size = new System.Drawing.Size(121, 21);
            this.comboBoxComPort.TabIndex = 0;
            this.comboBoxComPort.Text = "COM8";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.labelConnectionStatus);
            this.groupBox2.Controls.Add(this.labelStatus);
            this.groupBox2.Controls.Add(this.buttonCloseConnection);
            this.groupBox2.Controls.Add(this.buttonOpenConnection);
            this.groupBox2.Location = new System.Drawing.Point(12, 281);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(315, 182);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Komunikacja z robotem";
            // 
            // labelConnectionStatus
            // 
            this.labelConnectionStatus.AutoSize = true;
            this.labelConnectionStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelConnectionStatus.Location = new System.Drawing.Point(117, 126);
            this.labelConnectionStatus.Name = "labelConnectionStatus";
            this.labelConnectionStatus.Size = new System.Drawing.Size(84, 20);
            this.labelConnectionStatus.TabIndex = 3;
            this.labelConnectionStatus.Text = "OFFLINE";
            this.labelConnectionStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // labelStatus
            // 
            this.labelStatus.AutoSize = true;
            this.labelStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelStatus.Location = new System.Drawing.Point(71, 91);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(171, 20);
            this.labelStatus.TabIndex = 2;
            this.labelStatus.Text = "STAN POŁĄCZENIA";
            // 
            // buttonCloseConnection
            // 
            this.buttonCloseConnection.Location = new System.Drawing.Point(199, 36);
            this.buttonCloseConnection.Name = "buttonCloseConnection";
            this.buttonCloseConnection.Size = new System.Drawing.Size(93, 34);
            this.buttonCloseConnection.TabIndex = 1;
            this.buttonCloseConnection.Text = "ROZŁĄCZ";
            this.buttonCloseConnection.UseVisualStyleBackColor = true;
            this.buttonCloseConnection.Click += new System.EventHandler(this.buttonCloseConnection_Click);
            // 
            // buttonOpenConnection
            // 
            this.buttonOpenConnection.Location = new System.Drawing.Point(22, 36);
            this.buttonOpenConnection.Name = "buttonOpenConnection";
            this.buttonOpenConnection.Size = new System.Drawing.Size(95, 34);
            this.buttonOpenConnection.TabIndex = 0;
            this.buttonOpenConnection.Text = "POŁĄCZ";
            this.buttonOpenConnection.UseVisualStyleBackColor = true;
            this.buttonOpenConnection.Click += new System.EventHandler(this.buttonOpenConnection_Click);
            // 
            // tabControlMode
            // 
            this.tabControlMode.Controls.Add(this.tabPageAuto);
            this.tabControlMode.Controls.Add(this.tabPageRemote);
            this.tabControlMode.Location = new System.Drawing.Point(343, 12);
            this.tabControlMode.Name = "tabControlMode";
            this.tabControlMode.SelectedIndex = 0;
            this.tabControlMode.Size = new System.Drawing.Size(778, 633);
            this.tabControlMode.TabIndex = 17;
            this.tabControlMode.SelectedIndexChanged += new System.EventHandler(this.tabControlMode_SelectedIndexChanged);
            // 
            // tabPageAuto
            // 
            this.tabPageAuto.Controls.Add(this.groupBox9);
            this.tabPageAuto.Location = new System.Drawing.Point(4, 22);
            this.tabPageAuto.Name = "tabPageAuto";
            this.tabPageAuto.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageAuto.Size = new System.Drawing.Size(770, 607);
            this.tabPageAuto.TabIndex = 0;
            this.tabPageAuto.Text = "Tryb autonomiczny";
            this.tabPageAuto.UseVisualStyleBackColor = true;
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.pictureBoxLoad);
            this.groupBox9.Controls.Add(this.textBoxMap);
            this.groupBox9.Controls.Add(this.label9);
            this.groupBox9.Controls.Add(this.label7);
            this.groupBox9.Controls.Add(this.labelRobotStatus);
            this.groupBox9.Controls.Add(this.buttonAutonomousStart);
            this.groupBox9.Location = new System.Drawing.Point(6, 6);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(755, 585);
            this.groupBox9.TabIndex = 6;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "CENTRUM STEROWANIA - TRYB AUTONOMICZNY";
            // 
            // pictureBoxLoad
            // 
            this.pictureBoxLoad.Image = global::RobotControlApp.Properties.Resources.load;
            this.pictureBoxLoad.Location = new System.Drawing.Point(647, 34);
            this.pictureBoxLoad.Name = "pictureBoxLoad";
            this.pictureBoxLoad.Size = new System.Drawing.Size(75, 64);
            this.pictureBoxLoad.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxLoad.TabIndex = 7;
            this.pictureBoxLoad.TabStop = false;
            this.pictureBoxLoad.Visible = false;
            // 
            // textBoxMap
            // 
            this.textBoxMap.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.textBoxMap.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.textBoxMap.Location = new System.Drawing.Point(6, 120);
            this.textBoxMap.Multiline = true;
            this.textBoxMap.Name = "textBoxMap";
            this.textBoxMap.Size = new System.Drawing.Size(740, 460);
            this.textBoxMap.TabIndex = 6;
            this.textBoxMap.UseSystemPasswordChar = true;
            this.textBoxMap.WordWrap = false;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.BackColor = System.Drawing.Color.Peru;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label9.ForeColor = System.Drawing.SystemColors.Info;
            this.label9.Location = new System.Drawing.Point(105, 97);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(467, 20);
            this.label9.TabIndex = 5;
            this.label9.Text = "POMIAROWANIE POMIESZCZEŃ - PREZENTACJA WYNIKÓW";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label7.Location = new System.Drawing.Point(33, 37);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(156, 20);
            this.label7.TabIndex = 1;
            this.label7.Text = "STATUS ROBOTA";
            // 
            // labelRobotStatus
            // 
            this.labelRobotStatus.AutoSize = true;
            this.labelRobotStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelRobotStatus.Location = new System.Drawing.Point(195, 38);
            this.labelRobotStatus.Name = "labelRobotStatus";
            this.labelRobotStatus.Size = new System.Drawing.Size(97, 18);
            this.labelRobotStatus.TabIndex = 2;
            this.labelRobotStatus.Text = "BEZCZYNNY";
            // 
            // buttonAutonomousStart
            // 
            this.buttonAutonomousStart.Location = new System.Drawing.Point(425, 34);
            this.buttonAutonomousStart.Name = "buttonAutonomousStart";
            this.buttonAutonomousStart.Size = new System.Drawing.Size(145, 29);
            this.buttonAutonomousStart.TabIndex = 0;
            this.buttonAutonomousStart.Text = "START";
            this.buttonAutonomousStart.UseVisualStyleBackColor = true;
            this.buttonAutonomousStart.Click += new System.EventHandler(this.buttonAutonomousStart_Click);
            // 
            // tabPageRemote
            // 
            this.tabPageRemote.Controls.Add(this.groupBox13);
            this.tabPageRemote.Location = new System.Drawing.Point(4, 22);
            this.tabPageRemote.Name = "tabPageRemote";
            this.tabPageRemote.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageRemote.Size = new System.Drawing.Size(770, 607);
            this.tabPageRemote.TabIndex = 1;
            this.tabPageRemote.Text = "Zdalne sterowanie - tryb ręczny";
            this.tabPageRemote.UseVisualStyleBackColor = true;
            // 
            // groupBox13
            // 
            this.groupBox13.Controls.Add(this.groupBox12);
            this.groupBox13.Controls.Add(this.groupBox10);
            this.groupBox13.Controls.Add(this.groupBox11);
            this.groupBox13.Location = new System.Drawing.Point(6, 6);
            this.groupBox13.Name = "groupBox13";
            this.groupBox13.Size = new System.Drawing.Size(755, 585);
            this.groupBox13.TabIndex = 16;
            this.groupBox13.TabStop = false;
            this.groupBox13.Text = "CENTRUM STEROWANIA - TRYB ZDALNEGO STEROWANIA";
            // 
            // groupBox12
            // 
            this.groupBox12.Controls.Add(this.buttonForward);
            this.groupBox12.Controls.Add(this.buttonReverse);
            this.groupBox12.Controls.Add(this.buttonLeft);
            this.groupBox12.Controls.Add(this.buttonRight);
            this.groupBox12.Location = new System.Drawing.Point(564, 197);
            this.groupBox12.Name = "groupBox12";
            this.groupBox12.Size = new System.Drawing.Size(175, 389);
            this.groupBox12.TabIndex = 15;
            this.groupBox12.TabStop = false;
            this.groupBox12.Text = "Kontrola położenia";
            // 
            // buttonForward
            // 
            this.buttonForward.Image = global::RobotControlApp.Properties.Resources.forwardarrow4;
            this.buttonForward.Location = new System.Drawing.Point(31, 79);
            this.buttonForward.Name = "buttonForward";
            this.buttonForward.Size = new System.Drawing.Size(116, 49);
            this.buttonForward.TabIndex = 3;
            this.buttonForward.Text = "Przód ";
            this.buttonForward.UseVisualStyleBackColor = true;
            this.buttonForward.Click += new System.EventHandler(this.button2_Click);
            // 
            // buttonReverse
            // 
            this.buttonReverse.Image = global::RobotControlApp.Properties.Resources.reversearrow1;
            this.buttonReverse.Location = new System.Drawing.Point(31, 244);
            this.buttonReverse.Name = "buttonReverse";
            this.buttonReverse.Size = new System.Drawing.Size(116, 56);
            this.buttonReverse.TabIndex = 4;
            this.buttonReverse.Text = "Tył ";
            this.buttonReverse.UseVisualStyleBackColor = true;
            this.buttonReverse.Click += new System.EventHandler(this.button3_Click);
            // 
            // buttonLeft
            // 
            this.buttonLeft.Image = global::RobotControlApp.Properties.Resources.leftarrow1;
            this.buttonLeft.Location = new System.Drawing.Point(31, 133);
            this.buttonLeft.Name = "buttonLeft";
            this.buttonLeft.Size = new System.Drawing.Size(50, 105);
            this.buttonLeft.TabIndex = 5;
            this.buttonLeft.Text = "Lewo";
            this.buttonLeft.UseVisualStyleBackColor = true;
            this.buttonLeft.Click += new System.EventHandler(this.button4_Click);
            // 
            // buttonRight
            // 
            this.buttonRight.Image = global::RobotControlApp.Properties.Resources.rightarrow1;
            this.buttonRight.Location = new System.Drawing.Point(97, 133);
            this.buttonRight.Name = "buttonRight";
            this.buttonRight.Size = new System.Drawing.Size(50, 105);
            this.buttonRight.TabIndex = 6;
            this.buttonRight.Text = "Prawo";
            this.buttonRight.UseVisualStyleBackColor = true;
            this.buttonRight.Click += new System.EventHandler(this.button5_Click);
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.pictureBox1);
            this.groupBox10.Controls.Add(this.groupBox3);
            this.groupBox10.Controls.Add(this.groupBox4);
            this.groupBox10.Controls.Add(this.groupBox5);
            this.groupBox10.Controls.Add(this.groupBox6);
            this.groupBox10.Location = new System.Drawing.Point(13, 277);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(554, 309);
            this.groupBox10.TabIndex = 13;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "Wskazania odległości";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::RobotControlApp.Properties.Resources.robottop2;
            this.pictureBox1.Location = new System.Drawing.Point(162, 71);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(216, 201);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.labelDistance0);
            this.groupBox3.Location = new System.Drawing.Point(396, 90);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(149, 54);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Czujnik prawy - front";
            // 
            // labelDistance0
            // 
            this.labelDistance0.AutoSize = true;
            this.labelDistance0.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelDistance0.Location = new System.Drawing.Point(29, 22);
            this.labelDistance0.Name = "labelDistance0";
            this.labelDistance0.Size = new System.Drawing.Size(43, 20);
            this.labelDistance0.TabIndex = 0;
            this.labelDistance0.Text = "0 cm";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.labelDistance1);
            this.groupBox4.Location = new System.Drawing.Point(7, 132);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(149, 54);
            this.groupBox4.TabIndex = 2;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Czujnik lewy";
            // 
            // labelDistance1
            // 
            this.labelDistance1.AutoSize = true;
            this.labelDistance1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelDistance1.Location = new System.Drawing.Point(23, 22);
            this.labelDistance1.Name = "labelDistance1";
            this.labelDistance1.Size = new System.Drawing.Size(43, 20);
            this.labelDistance1.TabIndex = 1;
            this.labelDistance1.Text = "0 cm";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.labelDistance2);
            this.groupBox5.Location = new System.Drawing.Point(396, 179);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(149, 54);
            this.groupBox5.TabIndex = 2;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Czujnik prawy - tył";
            // 
            // labelDistance2
            // 
            this.labelDistance2.AutoSize = true;
            this.labelDistance2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelDistance2.Location = new System.Drawing.Point(25, 24);
            this.labelDistance2.Name = "labelDistance2";
            this.labelDistance2.Size = new System.Drawing.Size(43, 20);
            this.labelDistance2.TabIndex = 2;
            this.labelDistance2.Text = "0 cm";
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.labelDistance3);
            this.groupBox6.Location = new System.Drawing.Point(212, 13);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(149, 52);
            this.groupBox6.TabIndex = 2;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Czujnik przedni";
            // 
            // labelDistance3
            // 
            this.labelDistance3.AutoSize = true;
            this.labelDistance3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelDistance3.Location = new System.Drawing.Point(24, 20);
            this.labelDistance3.Name = "labelDistance3";
            this.labelDistance3.Size = new System.Drawing.Size(43, 20);
            this.labelDistance3.TabIndex = 3;
            this.labelDistance3.Text = "0 cm";
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.pictureBox2);
            this.groupBox11.Controls.Add(this.groupBox7);
            this.groupBox11.Controls.Add(this.groupBox8);
            this.groupBox11.Controls.Add(this.textBoxtestowy);
            this.groupBox11.Location = new System.Drawing.Point(13, 19);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(726, 265);
            this.groupBox11.TabIndex = 14;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "Wskazania pochylenia";
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = global::RobotControlApp.Properties.Resources.robotfront;
            this.pictureBox2.Location = new System.Drawing.Point(258, 36);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(217, 182);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 7;
            this.pictureBox2.TabStop = false;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.labelAngle1);
            this.groupBox7.Controls.Add(this.pictureBox3);
            this.groupBox7.Location = new System.Drawing.Point(18, 71);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(223, 181);
            this.groupBox7.TabIndex = 8;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Nachylenie podłużne";
            // 
            // labelAngle1
            // 
            this.labelAngle1.AutoSize = true;
            this.labelAngle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelAngle1.Location = new System.Drawing.Point(161, 41);
            this.labelAngle1.Name = "labelAngle1";
            this.labelAngle1.Size = new System.Drawing.Size(36, 20);
            this.labelAngle1.TabIndex = 11;
            this.labelAngle1.Text = "0 %";
            // 
            // pictureBox3
            // 
            this.pictureBox3.Image = global::RobotControlApp.Properties.Resources.alfastrong;
            this.pictureBox3.Location = new System.Drawing.Point(6, 19);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(149, 156);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox3.TabIndex = 10;
            this.pictureBox3.TabStop = false;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.labelAngle2);
            this.groupBox8.Controls.Add(this.pictureBox4);
            this.groupBox8.Location = new System.Drawing.Point(481, 34);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(239, 91);
            this.groupBox8.TabIndex = 11;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Nachylenie poprzeczne";
            // 
            // labelAngle2
            // 
            this.labelAngle2.AutoSize = true;
            this.labelAngle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelAngle2.Location = new System.Drawing.Point(178, 48);
            this.labelAngle2.Name = "labelAngle2";
            this.labelAngle2.Size = new System.Drawing.Size(36, 20);
            this.labelAngle2.TabIndex = 11;
            this.labelAngle2.Text = "0 %";
            // 
            // pictureBox4
            // 
            this.pictureBox4.Image = global::RobotControlApp.Properties.Resources.alfaright;
            this.pictureBox4.Location = new System.Drawing.Point(6, 19);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(149, 60);
            this.pictureBox4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox4.TabIndex = 10;
            this.pictureBox4.TabStop = false;
            // 
            // textBoxtestowy
            // 
            this.textBoxtestowy.Location = new System.Drawing.Point(350, 163);
            this.textBoxtestowy.Multiline = true;
            this.textBoxtestowy.Name = "textBoxtestowy";
            this.textBoxtestowy.Size = new System.Drawing.Size(152, 89);
            this.textBoxtestowy.TabIndex = 12;
            this.textBoxtestowy.Visible = false;
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // pictureBox5
            // 
            this.pictureBox5.Image = global::RobotControlApp.Properties.Resources.logo;
            this.pictureBox5.Location = new System.Drawing.Point(87, 496);
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size(149, 133);
            this.pictureBox5.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox5.TabIndex = 18;
            this.pictureBox5.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1126, 648);
            this.Controls.Add(this.pictureBox5);
            this.Controls.Add(this.tabControlMode);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Prototyp pojazdu autonomicznego do pomiarowania pomieszczen wewnatrz budynku";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Leave += new System.EventHandler(this.Form1_Leave);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.tabControlMode.ResumeLayout(false);
            this.tabPageAuto.ResumeLayout(false);
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLoad)).EndInit();
            this.tabPageRemote.ResumeLayout(false);
            this.groupBox13.ResumeLayout(false);
            this.groupBox12.ResumeLayout(false);
            this.groupBox10.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBoxParityBits;
        private System.Windows.Forms.ComboBox comboBoxStopBits;
        private System.Windows.Forms.ComboBox comboBoxDataBits;
        private System.Windows.Forms.ComboBox comboBoxBaudRate;
        private System.Windows.Forms.ComboBox comboBoxComPort;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label labelConnectionStatus;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.Button buttonCloseConnection;
        private System.Windows.Forms.Button buttonOpenConnection;
        private System.Windows.Forms.TabControl tabControlMode;
        private System.Windows.Forms.TabPage tabPageAuto;
        private System.Windows.Forms.Label labelRobotStatus;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button buttonAutonomousStart;
        private System.Windows.Forms.TabPage tabPageRemote;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Button buttonRight;
        private System.Windows.Forms.Button buttonLeft;
        private System.Windows.Forms.Button buttonReverse;
        private System.Windows.Forms.Button buttonForward;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Label labelDistance3;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label labelDistance2;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label labelDistance1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label labelDistance0;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Label labelAngle2;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.Label labelAngle1;
        public System.Windows.Forms.TextBox textBoxtestowy;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.PictureBox pictureBoxLoad;
        private System.Windows.Forms.PictureBox pictureBox5;
        private System.Windows.Forms.TextBox textBoxMap;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.GroupBox groupBox12;
        private System.Windows.Forms.GroupBox groupBox13;
    }
}

