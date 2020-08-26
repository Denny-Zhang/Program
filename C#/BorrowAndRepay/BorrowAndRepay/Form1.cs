using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BorrowAndRepay
{
    public partial class Form1 : Form
    {
        Person my, friend;
        public Form1()
        {
            InitializeComponent();
        }

        private void submitButton_Click(object sender, EventArgs e)
        {
            myNameLabel.Text = myTextBox.Text;
            friendNameLabel.Text = friendTextBox.Text;
            my = new Person(myNameLabel.Text, Int32.Parse(myMoneyLabel.Text));
            friend = new Person(friendNameLabel.Text, Int32.Parse(friendMoneyLabel.Text));

            myTextBox.Enabled = false;
            friendTextBox.Enabled = false;
            submitButton.Enabled = false;
            borrowButton.Enabled = true;
            repayButton.Enabled = true;
   
            borrowButton.Text = "跟" + friend.name + "借 1000$";
            repayButton.Text = "還給" + friend.name + " 1000$";
        }

        private void borrowButton_Click(object sender, EventArgs e)
        {
            my.result(friend);
            updateMoney();
        }

        private void repayButton_Click(object sender, EventArgs e)
        {
            friend.result(my);
            updateMoney();
        }
        private void updateMoney()
        {
            myMoneyLabel.Text = my.money.ToString();
            friendMoneyLabel.Text = friend.money.ToString();
        }
    }
}
