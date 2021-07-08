using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotControlApp
{

    public partial class Form1 : Form
    {
        //bool autonomous_mode = false; //initial state - remote control
        bool remote_mode = true;
        bool automode = true;
        bool autoworking = false;
        string stringMapRepresentation = "";
        string all_sensors_data = "";
        static String sensor_data = "";
        string received_data;

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonOpenConnection_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = comboBoxComPort.Text;
                serialPort1.BaudRate = Convert.ToInt32(comboBoxBaudRate.Text);
                serialPort1.DataBits = Convert.ToInt32(comboBoxDataBits.Text);
                serialPort1.StopBits = (StopBits)Enum.Parse(typeof(StopBits), comboBoxStopBits.Text);
                string parity;
                if (comboBoxParityBits.Text == "Parzysty") parity = "Odd";
                else if (comboBoxParityBits.Text == "Nieparzysty") parity = "Even";
                else parity = "None";
                serialPort1.Parity = (Parity)Enum.Parse(typeof(Parity), parity);
                serialPort1.Open();
                labelConnectionStatus.BackColor = Color.YellowGreen;
                labelConnectionStatus.Text = "ONLINE";
                pictureBoxLoad.Visible = false;
            }
            catch (Exception exc)
            {
                MessageBox.Show("Nie można nawiązać tego połączenia: " + exc.Message, "Wystąpił błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void buttonCloseConnection_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (autoworking)
                {
                    pictureBoxLoad.Visible = false;
                    labelRobotStatus.Text = "BEZCZYNNY";
                    buttonAutonomousStart.Text = "START";
                    send_command("<"); //end of measurements
                    autoworking = false;
                }
                serialPort1.Close();
                labelConnectionStatus.Text = "OFFLINE";
                labelConnectionStatus.BackColor = Color.Red;
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            received_data = serialPort1.ReadExisting();
            this.Invoke(new EventHandler(printData));
        }

        private void printData(object sender, EventArgs e)
        {

            if (!automode)
            {
                if (received_data[received_data.Length - 1] == '\n') //[received_data] == "\n"
                {
                    textBoxtestowy.Text = "";
                    textBoxtestowy.Text = all_sensors_data;
                    string[] splited_sensors_data = all_sensors_data.Split(' ');
                    var distance_labels = new List<Label> { labelDistance0, labelDistance1, labelDistance2, labelDistance3 };
                    for (int i = 0; i < splited_sensors_data.Count(); i++)
                    {
                        splited_sensors_data[i] = splited_sensors_data[i].Replace("\n", "");
                        splited_sensors_data[i] = splited_sensors_data[i].Replace("\r", "");
                    }
                    for (int i = 0; i < 4; i++) //4 - number of distance labels
                    {
                        if (i <= splited_sensors_data.Count() - 1)
                        {
                            distance_labels.ElementAt(i).Text = splited_sensors_data[i] + " cm";
                        }
                        else
                            distance_labels.ElementAt(i).Text = "0 cm";
                    }
                    labelAngle2.Text = (splited_sensors_data.Count() > 4) ? (splited_sensors_data[4] + " %") : "0 %";
                    labelAngle1.Text = (splited_sensors_data.Count() > 5) ? (splited_sensors_data[5] + " %") : "0 %";
                    all_sensors_data = "";
                }
                else
                {
                    all_sensors_data += received_data;
                }
            }
            
            
            {
                
                if (received_data.Length > 0 &&  received_data[received_data.Length - 1] == '*') //check if robot send info about end of measurements
                {
                    labelRobotStatus.Text = "POMIARY ZAKOŃCZONE";
                    buttonAutonomousStart.Text = "START";
                    pictureBoxLoad.Visible = false;
                    autoworking = false;
                    //textBoxMap.Text = stringMapRepresentation;
                }
                //all_sensors_data += received_data;
                if (received_data[received_data.Length - 1] == '.')
                {
                    textBoxMap.Text = stringMapRepresentation;
                    stringMapRepresentation = "";
                }
                else
                {
                    stringMapRepresentation += received_data;
                }
                
            }
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            labelConnectionStatus.BackColor = Color.Red;


            string[] comPorts = SerialPort.GetPortNames();
            comboBoxComPort.Items.AddRange(comPorts);
        }
        

        private void buttonAutonomousStart_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                MessageBox.Show("Brak komunikacji z robotem!", "Nie można wykonać polecenia", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (buttonAutonomousStart.Text == "START")
            {

                stringMapRepresentation = "";
                all_sensors_data = "";
                sensor_data = "";
                received_data = "";

                labelRobotStatus.Text = "PRACA";
                buttonAutonomousStart.Text = "STOP";
                pictureBoxLoad.Visible = true;
                send_command(">"); //send '>' to end measurements
                autoworking = true;
            }
            else if (buttonAutonomousStart.Text == "STOP")
            {
                pictureBoxLoad.Visible = false;
                labelRobotStatus.Text = "BEZCZYNNY";
                buttonAutonomousStart.Text = "START";
                send_command("<"); //end of measurements
                autoworking = false;
            }
        }

        private void tabControlMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (tabControlMode.SelectedTab.Name == "tabPageRemote")
            {
                if (buttonAutonomousStart.Text != "START")
                {
                    tabControlMode.SelectedTab = tabPageAuto;
                    MessageBox.Show("Przed prejściem do trybu ręcznego sterowania wyłącz pomiar automatyczny.", "Praca autonomiczna w toku!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
                send_command("1");//wyslanie 2 oznacza przejscie w tryb autonomiczny
                automode = false;
            }
            if (tabControlMode.SelectedTab.Name == "tabPageAuto")
            {
                send_command("2");//wyslanie 2 oznacza przejscie w tryb autonomiczny
                automode = true;
            }
        }

        private void send_command(string command)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write(command);
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            send_command("w");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            send_command("d");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            send_command("s");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            send_command("a");
        }

        private void Form1_Leave(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                labelConnectionStatus.Text = "OFFLINE";
                labelConnectionStatus.BackColor = Color.Red;
            }
        }
    }
}
