namespace BorrowAndRepay
{
    partial class Form1
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置 Managed 資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.submitButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.myTextBox = new System.Windows.Forms.TextBox();
            this.friendTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.myMoneyLabel = new System.Windows.Forms.Label();
            this.myNameLabel = new System.Windows.Forms.Label();
            this.friendNameLabel = new System.Windows.Forms.Label();
            this.friendMoneyLabel = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.borrowButton = new System.Windows.Forms.Button();
            this.repayButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("新細明體", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label1.Location = new System.Drawing.Point(22, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(162, 21);
            this.label1.TabIndex = 0;
            this.label1.Text = "請輸入我的名字:";
            // 
            // submitButton
            // 
            this.submitButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.submitButton.Location = new System.Drawing.Point(360, 12);
            this.submitButton.Name = "submitButton";
            this.submitButton.Size = new System.Drawing.Size(130, 75);
            this.submitButton.TabIndex = 1;
            this.submitButton.Text = "確認";
            this.submitButton.UseVisualStyleBackColor = true;
            this.submitButton.Click += new System.EventHandler(this.submitButton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("新細明體", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label2.Location = new System.Drawing.Point(22, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(183, 21);
            this.label2.TabIndex = 2;
            this.label2.Text = "請輸入朋友的名字:";
            // 
            // myTextBox
            // 
            this.myTextBox.Font = new System.Drawing.Font("新細明體", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.myTextBox.Location = new System.Drawing.Point(221, 12);
            this.myTextBox.Name = "myTextBox";
            this.myTextBox.Size = new System.Drawing.Size(100, 33);
            this.myTextBox.TabIndex = 3;
            // 
            // friendTextBox
            // 
            this.friendTextBox.Font = new System.Drawing.Font("新細明體", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.friendTextBox.Location = new System.Drawing.Point(221, 54);
            this.friendTextBox.Name = "friendTextBox";
            this.friendTextBox.Size = new System.Drawing.Size(100, 33);
            this.friendTextBox.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label3.Location = new System.Drawing.Point(35, 132);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(76, 16);
            this.label3.TabIndex = 5;
            this.label3.Text = "我的名字:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label4.Location = new System.Drawing.Point(35, 169);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(60, 16);
            this.label4.TabIndex = 6;
            this.label4.Text = "我的$$:";
            // 
            // myMoneyLabel
            // 
            this.myMoneyLabel.AutoSize = true;
            this.myMoneyLabel.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.myMoneyLabel.Location = new System.Drawing.Point(128, 169);
            this.myMoneyLabel.Name = "myMoneyLabel";
            this.myMoneyLabel.Size = new System.Drawing.Size(16, 16);
            this.myMoneyLabel.TabIndex = 7;
            this.myMoneyLabel.Text = "0";
            // 
            // myNameLabel
            // 
            this.myNameLabel.AutoSize = true;
            this.myNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.myNameLabel.Location = new System.Drawing.Point(127, 128);
            this.myNameLabel.Name = "myNameLabel";
            this.myNameLabel.Size = new System.Drawing.Size(57, 20);
            this.myNameLabel.TabIndex = 8;
            this.myNameLabel.Text = "無名氏";
            // 
            // friendNameLabel
            // 
            this.friendNameLabel.AutoSize = true;
            this.friendNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.friendNameLabel.Location = new System.Drawing.Point(372, 128);
            this.friendNameLabel.Name = "friendNameLabel";
            this.friendNameLabel.Size = new System.Drawing.Size(57, 20);
            this.friendNameLabel.TabIndex = 12;
            this.friendNameLabel.Text = "無名氏";
            // 
            // friendMoneyLabel
            // 
            this.friendMoneyLabel.AutoSize = true;
            this.friendMoneyLabel.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.friendMoneyLabel.Location = new System.Drawing.Point(373, 169);
            this.friendMoneyLabel.Name = "friendMoneyLabel";
            this.friendMoneyLabel.Size = new System.Drawing.Size(48, 16);
            this.friendMoneyLabel.TabIndex = 11;
            this.friendMoneyLabel.Text = "20000";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label9.Location = new System.Drawing.Point(263, 169);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(76, 16);
            this.label9.TabIndex = 10;
            this.label9.Text = "朋友的$$:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label10.Location = new System.Drawing.Point(263, 132);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(92, 16);
            this.label10.TabIndex = 9;
            this.label10.Text = "朋友的名字:";
            // 
            // borrowButton
            // 
            this.borrowButton.Enabled = false;
            this.borrowButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.borrowButton.Location = new System.Drawing.Point(26, 202);
            this.borrowButton.Name = "borrowButton";
            this.borrowButton.Size = new System.Drawing.Size(464, 58);
            this.borrowButton.TabIndex = 13;
            this.borrowButton.Text = "跟 XXX借 1000$";
            this.borrowButton.UseVisualStyleBackColor = true;
            this.borrowButton.Click += new System.EventHandler(this.borrowButton_Click);
            // 
            // repayButton
            // 
            this.repayButton.Enabled = false;
            this.repayButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.repayButton.Location = new System.Drawing.Point(26, 278);
            this.repayButton.Name = "repayButton";
            this.repayButton.Size = new System.Drawing.Size(464, 59);
            this.repayButton.TabIndex = 14;
            this.repayButton.Text = "還給XXX 1000$";
            this.repayButton.UseVisualStyleBackColor = true;
            this.repayButton.Click += new System.EventHandler(this.repayButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(531, 366);
            this.Controls.Add(this.repayButton);
            this.Controls.Add(this.borrowButton);
            this.Controls.Add(this.friendNameLabel);
            this.Controls.Add(this.friendMoneyLabel);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.myNameLabel);
            this.Controls.Add(this.myMoneyLabel);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.friendTextBox);
            this.Controls.Add(this.myTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.submitButton);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("新細明體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.Name = "Form1";
            this.Text = "借還錢程式";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button submitButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox myTextBox;
        private System.Windows.Forms.TextBox friendTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label myMoneyLabel;
        private System.Windows.Forms.Label myNameLabel;
        private System.Windows.Forms.Label friendNameLabel;
        private System.Windows.Forms.Label friendMoneyLabel;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button borrowButton;
        private System.Windows.Forms.Button repayButton;
    }
}

