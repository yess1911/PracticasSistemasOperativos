﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ProductorConsumidor
{
    public partial class Form1 : Form
    {
        private Container container;
        public Form1()
        {
            container = new Container();
            InitializeComponent();
        }

        public void ChangeStateLabel(int c, int p)
        {
            switch (p)
            {
                case Constants.WORKING:
                    producerState.Text = "Trabajando";
                    producerState.BackColor = Color.ForestGreen;
                    producerState.Refresh();
                    label1.Text = "Productor";
                    label1.BackColor = Color.ForestGreen;
                    label1.Refresh();
                    break;
                case Constants.TRYING:
                    producerState.Text = "Intentando";
                    producerState.BackColor = Color.Gold;
                    producerState.Refresh();
                    label1.Text = "Productor";
                    label1.BackColor = Color.Gold;
                    label1.Refresh();
                    break;
                default:
                    producerState.Text = "Durmiendo";
                    producerState.BackColor = Color.Red;
                    producerState.Refresh();
                    label1.Text = "Productor";
                    label1.BackColor = Color.Red;
                    label1.Refresh();
                    break;
            }
            switch (c)
            {
                case Constants.WORKING:
                    consumerState.Text = "Trabajando";
                    consumerState.BackColor = Color.ForestGreen;
                    consumerState.Refresh();
                    label27.Text = "Consumidor";
                    label27.BackColor = Color.ForestGreen;
                    label27.Refresh();
                    break;
                case Constants.TRYING:
                    consumerState.Text = "Intentando";
                    consumerState.BackColor = Color.Gold;
                    producerState.Refresh();
                    label27.Text = "Consumidor";
                    label27.BackColor = Color.Gold;
                    label27.Refresh();
                    break;
                default:
                    consumerState.Text = "Durmiendo";
                    consumerState.BackColor = Color.Red;
                    consumerState.Refresh();
                    label27.Text = "Consumidor";
                    label27.BackColor = Color.Red;
                    label27.Refresh();
                    break;
            }
        }

        public void SetImage(int index, int turn)
        {
            Bitmap bmp = new Bitmap("..\\..\\Rosquilla.png");
            PictureBox pb = new PictureBox();

            switch (index)
            {
                case 0: pb = pictureBox1; break;
                case 1: pb = pictureBox2; break;
                case 2: pb = pictureBox3; break;
                case 3: pb = pictureBox4; break;
                case 4: pb = pictureBox5; break;
                case 5: pb = pictureBox6; break;
                case 6: pb = pictureBox7; break;
                case 7: pb = pictureBox8; break;
                case 8: pb = pictureBox9; break;
                case 9: pb = pictureBox10; break;
                case 10: pb = pictureBox11; break;
                case 11: pb = pictureBox12; break;
                case 12: pb = pictureBox13; break;
                case 13: pb = pictureBox14; break;
                case 14: pb = pictureBox15; break;
                case 15: pb = pictureBox16; break;
                case 16: pb = pictureBox17; break;
                case 17: pb = pictureBox18; break;
                case 18: pb = pictureBox19; break;
                case 19: pb = pictureBox20; break;
                case 20: pb = pictureBox21; break;
                case 21: pb = pictureBox22; break;
                case 22: pb = pictureBox23; break;
                case 23: pb = pictureBox24; break;
                case 24: pb = pictureBox25; break;
                    
            }

            if (turn == Constants.PRODUCER_TURN)
            {
                pb.Image = bmp;
            }
            else
            {
                if (pb.Image != null)
                {
                    pb.Image = null;
                }
            }
        }

        public async void start()
        {
            Consumer consumer = new Consumer();
            Producer producer = new Producer();
            int moves, i;
            do
            {
                moves = container.NextMoves();
                for (i = 0; i < moves; ++i)
                {
                    await Task.Delay(1000);
                    consumer = container.GetConsumer();
                    producer = container.GetProducer();

                    if (container.GetCurrentTurn() == Constants.CONSUMER_TURN)
                    {
                        if (consumer.getState() == Constants.WORKING)
                        {
                            if (container.setAction(consumer.getCurrentPos(), consumer.Consume()))
                            {
                                SetImage(consumer.getCurrentPos(), Constants.CONSUMER_TURN);
                                consumer = container.GetConsumer();
                                consumer.setCurrentPos(consumer.getCurrentPos() + 1);
                            }
                            if (consumer.getCurrentPos() == Constants.CONTAINER_SIZE)
                            {
                                consumer.setCurrentPos(0);
                            }
                        }
                        if (consumer.getState() == Constants.TRYING)
                        {
                            ChangeStateLabel(consumer.getState(), producer.getState());
                            break;
                        }
                    }
                    else
                    {
                        if (producer.getState() == Constants.WORKING)
                        { 
                            if (container.setAction(producer.getCurrentPos(), producer.Produce()))
                            {
                                SetImage(producer.getCurrentPos(), Constants.PRODUCER_TURN);
                                producer = container.GetProducer();
                                producer.setCurrentPos(producer.getCurrentPos() + 1);
                            }
                            if (producer.getCurrentPos() == Constants.CONTAINER_SIZE)
                            {
                                producer.setCurrentPos(0);
                            }
                        }
                        if (producer.getState() == Constants.TRYING)
                        {
                            ChangeStateLabel(consumer.getState(), producer.getState());
                            break;
                        }
                    }
                    ChangeStateLabel(consumer.getState(),producer.getState());
                    Update();
                }
            } while (true);
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == (Keys.Escape))
            {
                this.Close();
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void startBT_Click(object sender, EventArgs e)
        {
            start();
            startBT.Enabled = false;
            startBT.Visible = false;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void pictureBox10_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void producerLB_Click(object sender, EventArgs e)
        {

        }

        private void textBox26_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox25_TextChanged(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox8_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void consumerState_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click_2(object sender, EventArgs e)
        {

        }

        private void label27_Click(object sender, EventArgs e)
        {

        }

        private void label29_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox26_Click(object sender, EventArgs e)
        {

        }

        private void label28_Click(object sender, EventArgs e)
        {

        }
    }
}
