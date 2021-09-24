namespace skyscraperapp
{
    partial class Main
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.size = new System.Windows.Forms.NumericUpDown();
            this.solveBtn = new System.Windows.Forms.Button();
            this.clearBtn = new System.Windows.Forms.Button();
            this._7x71 = new skyscraperapp._7x7();
            this._6x61 = new skyscraperapp._6x6();
            this._5x51 = new skyscraperapp._5x5();
            this._4x41 = new skyscraperapp._4x4();
            this._8x81 = new skyscraperapp._8x8();
            ((System.ComponentModel.ISupportInitialize)(this.size)).BeginInit();
            this.SuspendLayout();
            // 
            // size
            // 
            this.size.Location = new System.Drawing.Point(24, 33);
            this.size.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.size.Minimum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.size.Name = "size";
            this.size.Size = new System.Drawing.Size(109, 20);
            this.size.TabIndex = 0;
            this.size.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.size.ValueChanged += new System.EventHandler(this.size_ValueChanged);
            // 
            // solveBtn
            // 
            this.solveBtn.Location = new System.Drawing.Point(463, 33);
            this.solveBtn.Name = "solveBtn";
            this.solveBtn.Size = new System.Drawing.Size(102, 45);
            this.solveBtn.TabIndex = 66;
            this.solveBtn.Text = "Solve";
            this.solveBtn.UseVisualStyleBackColor = true;
            this.solveBtn.Click += new System.EventHandler(this.solve);
            // 
            // clearBtn
            // 
            this.clearBtn.Location = new System.Drawing.Point(463, 84);
            this.clearBtn.Name = "clearBtn";
            this.clearBtn.Size = new System.Drawing.Size(102, 45);
            this.clearBtn.TabIndex = 72;
            this.clearBtn.Text = "Clear";
            this.clearBtn.UseVisualStyleBackColor = true;
            this.clearBtn.Click += new System.EventHandler(this.clear);
            // 
            // _7x71
            // 
            this._7x71.Location = new System.Drawing.Point(24, 68);
            this._7x71.Name = "_7x71";
            this._7x71.Size = new System.Drawing.Size(449, 403);
            this._7x71.TabIndex = 70;
            this._7x71.Visible = false;
            // 
            // _6x61
            // 
            this._6x61.Location = new System.Drawing.Point(24, 68);
            this._6x61.Name = "_6x61";
            this._6x61.Size = new System.Drawing.Size(410, 368);
            this._6x61.TabIndex = 69;
            this._6x61.Visible = false;
            // 
            // _5x51
            // 
            this._5x51.Location = new System.Drawing.Point(24, 68);
            this._5x51.Name = "_5x51";
            this._5x51.Size = new System.Drawing.Size(374, 324);
            this._5x51.TabIndex = 68;
            this._5x51.Visible = false;
            // 
            // _4x41
            // 
            this._4x41.Location = new System.Drawing.Point(24, 68);
            this._4x41.Name = "_4x41";
            this._4x41.Size = new System.Drawing.Size(326, 290);
            this._4x41.TabIndex = 67;
            // 
            // _8x81
            // 
            this._8x81.Location = new System.Drawing.Point(24, 68);
            this._8x81.Name = "_8x81";
            this._8x81.Size = new System.Drawing.Size(490, 442);
            this._8x81.TabIndex = 71;
            this._8x81.Visible = false;
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(581, 529);
            this.Controls.Add(this.clearBtn);
            this.Controls.Add(this.solveBtn);
            this.Controls.Add(this.size);
            this.Controls.Add(this._8x81);
            this.Controls.Add(this._7x71);
            this.Controls.Add(this._6x61);
            this.Controls.Add(this._5x51);
            this.Controls.Add(this._4x41);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(597, 568);
            this.MinimumSize = new System.Drawing.Size(597, 568);
            this.Name = "Main";
            this.Text = "Skyscraper Solver";
            ((System.ComponentModel.ISupportInitialize)(this.size)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NumericUpDown size;
        private System.Windows.Forms.Button solveBtn;
        private _4x4 _4x41;
        private _5x5 _5x51;
        private _6x6 _6x61;
        private _7x7 _7x71;
        private System.Windows.Forms.Button clearBtn;
        private _8x8 _8x81;
    }
}

