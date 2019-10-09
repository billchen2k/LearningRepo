namespace FPainter
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.colorPicker = new System.Windows.Forms.ColorDialog();
            this.radPointer = new System.Windows.Forms.RadioButton();
            this.radLine = new System.Windows.Forms.RadioButton();
            this.panelTools = new System.Windows.Forms.Panel();
            this.grpToolSetting = new System.Windows.Forms.GroupBox();
            this.picColorYellow = new System.Windows.Forms.PictureBox();
            this.picColorGreen = new System.Windows.Forms.PictureBox();
            this.btnColorPicker = new System.Windows.Forms.Button();
            this.labWidth = new System.Windows.Forms.Label();
            this.picColorCustom = new System.Windows.Forms.PictureBox();
            this.trackWidth = new System.Windows.Forms.TrackBar();
            this.picColorRed = new System.Windows.Forms.PictureBox();
            this.picColorBlack = new System.Windows.Forms.PictureBox();
            this.picColorBlue = new System.Windows.Forms.PictureBox();
            this.radEraser = new System.Windows.Forms.RadioButton();
            this.radPolygon = new System.Windows.Forms.RadioButton();
            this.radPencil = new System.Windows.Forms.RadioButton();
            this.radRectangle = new System.Windows.Forms.RadioButton();
            this.radCircle = new System.Windows.Forms.RadioButton();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.文件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuNew = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.menuClose = new System.Windows.Forms.ToolStripMenuItem();
            this.关于ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuWebsite = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.menuAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.statColor = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statLabCordinate = new System.Windows.Forms.ToolStripStatusLabel();
            this.glCanvas = new SharpGL.OpenGLControl();
            this.panelTools.SuspendLayout();
            this.grpToolSetting.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picColorYellow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorGreen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorCustom)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorRed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorBlack)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorBlue)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.glCanvas)).BeginInit();
            this.SuspendLayout();
            // 
            // radPointer
            // 
            this.radPointer.AutoSize = true;
            this.radPointer.Checked = true;
            this.radPointer.Location = new System.Drawing.Point(28, 20);
            this.radPointer.Name = "radPointer";
            this.radPointer.Size = new System.Drawing.Size(90, 24);
            this.radPointer.TabIndex = 1;
            this.radPointer.TabStop = true;
            this.radPointer.Text = "指针工具";
            this.radPointer.UseVisualStyleBackColor = true;
            this.radPointer.CheckedChanged += new System.EventHandler(this.radPointer_CheckedChanged);
            // 
            // radLine
            // 
            this.radLine.AutoSize = true;
            this.radLine.Location = new System.Drawing.Point(28, 110);
            this.radLine.Name = "radLine";
            this.radLine.Size = new System.Drawing.Size(90, 24);
            this.radLine.TabIndex = 2;
            this.radLine.Text = "直线工具";
            this.radLine.UseVisualStyleBackColor = true;
            this.radLine.CheckedChanged += new System.EventHandler(this.radLine_CheckedChanged);
            // 
            // panelTools
            // 
            this.panelTools.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.panelTools.BackColor = System.Drawing.SystemColors.Control;
            this.panelTools.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelTools.Controls.Add(this.grpToolSetting);
            this.panelTools.Controls.Add(this.radEraser);
            this.panelTools.Controls.Add(this.radPolygon);
            this.panelTools.Controls.Add(this.radPencil);
            this.panelTools.Controls.Add(this.radRectangle);
            this.panelTools.Controls.Add(this.radCircle);
            this.panelTools.Controls.Add(this.radLine);
            this.panelTools.Controls.Add(this.radPointer);
            this.panelTools.Location = new System.Drawing.Point(0, 28);
            this.panelTools.Name = "panelTools";
            this.panelTools.Size = new System.Drawing.Size(180, 706);
            this.panelTools.TabIndex = 3;
            // 
            // grpToolSetting
            // 
            this.grpToolSetting.Controls.Add(this.picColorYellow);
            this.grpToolSetting.Controls.Add(this.picColorGreen);
            this.grpToolSetting.Controls.Add(this.btnColorPicker);
            this.grpToolSetting.Controls.Add(this.labWidth);
            this.grpToolSetting.Controls.Add(this.picColorCustom);
            this.grpToolSetting.Controls.Add(this.trackWidth);
            this.grpToolSetting.Controls.Add(this.picColorRed);
            this.grpToolSetting.Controls.Add(this.picColorBlack);
            this.grpToolSetting.Controls.Add(this.picColorBlue);
            this.grpToolSetting.Location = new System.Drawing.Point(28, 247);
            this.grpToolSetting.Name = "grpToolSetting";
            this.grpToolSetting.Size = new System.Drawing.Size(135, 341);
            this.grpToolSetting.TabIndex = 8;
            this.grpToolSetting.TabStop = false;
            this.grpToolSetting.Text = "工具选项";
            // 
            // picColorYellow
            // 
            this.picColorYellow.BackColor = System.Drawing.Color.Gold;
            this.picColorYellow.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picColorYellow.Location = new System.Drawing.Point(49, 239);
            this.picColorYellow.Name = "picColorYellow";
            this.picColorYellow.Size = new System.Drawing.Size(30, 30);
            this.picColorYellow.TabIndex = 12;
            this.picColorYellow.TabStop = false;
            this.picColorYellow.Click += new System.EventHandler(this.picColorYellow_Click);
            // 
            // picColorGreen
            // 
            this.picColorGreen.BackColor = System.Drawing.Color.LimeGreen;
            this.picColorGreen.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picColorGreen.Location = new System.Drawing.Point(13, 239);
            this.picColorGreen.Name = "picColorGreen";
            this.picColorGreen.Size = new System.Drawing.Size(30, 30);
            this.picColorGreen.TabIndex = 11;
            this.picColorGreen.TabStop = false;
            this.picColorGreen.Click += new System.EventHandler(this.picColorGreen_Click);
            // 
            // btnColorPicker
            // 
            this.btnColorPicker.Location = new System.Drawing.Point(13, 275);
            this.btnColorPicker.Name = "btnColorPicker";
            this.btnColorPicker.Size = new System.Drawing.Size(102, 36);
            this.btnColorPicker.TabIndex = 10;
            this.btnColorPicker.Text = "自定义颜色";
            this.btnColorPicker.UseVisualStyleBackColor = true;
            this.btnColorPicker.Click += new System.EventHandler(this.btnColorPicker_Click);
            // 
            // labWidth
            // 
            this.labWidth.AutoSize = true;
            this.labWidth.Location = new System.Drawing.Point(24, 166);
            this.labWidth.Name = "labWidth";
            this.labWidth.Size = new System.Drawing.Size(96, 20);
            this.labWidth.TabIndex = 1;
            this.labWidth.Text = "粗细（2px）";
            // 
            // picColorCustom
            // 
            this.picColorCustom.BackColor = System.Drawing.Color.White;
            this.picColorCustom.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picColorCustom.Location = new System.Drawing.Point(85, 239);
            this.picColorCustom.Name = "picColorCustom";
            this.picColorCustom.Size = new System.Drawing.Size(30, 30);
            this.picColorCustom.TabIndex = 9;
            this.picColorCustom.TabStop = false;
            this.picColorCustom.Click += new System.EventHandler(this.picColorCustom_Click);
            // 
            // trackWidth
            // 
            this.trackWidth.Location = new System.Drawing.Point(41, 36);
            this.trackWidth.Maximum = 50;
            this.trackWidth.Minimum = 1;
            this.trackWidth.Name = "trackWidth";
            this.trackWidth.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackWidth.Size = new System.Drawing.Size(56, 111);
            this.trackWidth.TabIndex = 0;
            this.trackWidth.Value = 2;
            this.trackWidth.Scroll += new System.EventHandler(this.trackWidth_Scroll);
            // 
            // picColorRed
            // 
            this.picColorRed.BackColor = System.Drawing.Color.Crimson;
            this.picColorRed.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picColorRed.Location = new System.Drawing.Point(85, 203);
            this.picColorRed.Name = "picColorRed";
            this.picColorRed.Size = new System.Drawing.Size(30, 30);
            this.picColorRed.TabIndex = 9;
            this.picColorRed.TabStop = false;
            this.picColorRed.Click += new System.EventHandler(this.picColorRed_Click);
            // 
            // picColorBlack
            // 
            this.picColorBlack.BackColor = System.Drawing.Color.Black;
            this.picColorBlack.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picColorBlack.Location = new System.Drawing.Point(13, 203);
            this.picColorBlack.Name = "picColorBlack";
            this.picColorBlack.Size = new System.Drawing.Size(30, 30);
            this.picColorBlack.TabIndex = 9;
            this.picColorBlack.TabStop = false;
            this.picColorBlack.Click += new System.EventHandler(this.picColorBlack_Click);
            // 
            // picColorBlue
            // 
            this.picColorBlue.BackColor = System.Drawing.Color.DodgerBlue;
            this.picColorBlue.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picColorBlue.Location = new System.Drawing.Point(49, 203);
            this.picColorBlue.Name = "picColorBlue";
            this.picColorBlue.Size = new System.Drawing.Size(30, 30);
            this.picColorBlue.TabIndex = 9;
            this.picColorBlue.TabStop = false;
            this.picColorBlue.Click += new System.EventHandler(this.picColorBlue_Click);
            // 
            // radEraser
            // 
            this.radEraser.AutoSize = true;
            this.radEraser.Location = new System.Drawing.Point(28, 80);
            this.radEraser.Name = "radEraser";
            this.radEraser.Size = new System.Drawing.Size(105, 24);
            this.radEraser.TabIndex = 7;
            this.radEraser.Text = "橡皮擦工具";
            this.radEraser.UseVisualStyleBackColor = true;
            this.radEraser.CheckedChanged += new System.EventHandler(this.radEraser_CheckedChanged);
            // 
            // radPolygon
            // 
            this.radPolygon.AutoSize = true;
            this.radPolygon.Location = new System.Drawing.Point(28, 200);
            this.radPolygon.Name = "radPolygon";
            this.radPolygon.Size = new System.Drawing.Size(105, 24);
            this.radPolygon.TabIndex = 6;
            this.radPolygon.Text = "多边形工具";
            this.radPolygon.UseVisualStyleBackColor = true;
            this.radPolygon.CheckedChanged += new System.EventHandler(this.radPolygon_CheckedChanged);
            // 
            // radPencil
            // 
            this.radPencil.AutoSize = true;
            this.radPencil.Location = new System.Drawing.Point(28, 50);
            this.radPencil.Name = "radPencil";
            this.radPencil.Size = new System.Drawing.Size(90, 24);
            this.radPencil.TabIndex = 5;
            this.radPencil.Text = "铅笔工具";
            this.radPencil.UseVisualStyleBackColor = true;
            this.radPencil.CheckedChanged += new System.EventHandler(this.radPencil_CheckedChanged);
            // 
            // radRectangle
            // 
            this.radRectangle.AutoSize = true;
            this.radRectangle.Location = new System.Drawing.Point(28, 170);
            this.radRectangle.Name = "radRectangle";
            this.radRectangle.Size = new System.Drawing.Size(90, 24);
            this.radRectangle.TabIndex = 4;
            this.radRectangle.Text = "矩形工具";
            this.radRectangle.UseVisualStyleBackColor = true;
            this.radRectangle.CheckedChanged += new System.EventHandler(this.radRectangle_CheckedChanged);
            // 
            // radCircle
            // 
            this.radCircle.AutoSize = true;
            this.radCircle.Location = new System.Drawing.Point(28, 140);
            this.radCircle.Name = "radCircle";
            this.radCircle.Size = new System.Drawing.Size(90, 24);
            this.radCircle.TabIndex = 3;
            this.radCircle.Text = "椭圆工具";
            this.radCircle.UseVisualStyleBackColor = true;
            this.radCircle.CheckedChanged += new System.EventHandler(this.radCircle_CheckedChanged);
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件ToolStripMenuItem,
            this.关于ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Margin = new System.Windows.Forms.Padding(3);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.menuStrip1.Size = new System.Drawing.Size(978, 28);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 文件ToolStripMenuItem
            // 
            this.文件ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuNew,
            this.toolStripMenuItem3,
            this.menuClose});
            this.文件ToolStripMenuItem.Name = "文件ToolStripMenuItem";
            this.文件ToolStripMenuItem.Size = new System.Drawing.Size(71, 24);
            this.文件ToolStripMenuItem.Text = "文件(&F)";
            // 
            // menuNew
            // 
            this.menuNew.Name = "menuNew";
            this.menuNew.Size = new System.Drawing.Size(144, 26);
            this.menuNew.Text = "新建(&N)";
            this.menuNew.Click += new System.EventHandler(this.menuNew_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(141, 6);
            // 
            // menuClose
            // 
            this.menuClose.Name = "menuClose";
            this.menuClose.Size = new System.Drawing.Size(144, 26);
            this.menuClose.Text = "关闭(&C)";
            this.menuClose.Click += new System.EventHandler(this.MenuClose_Click);
            // 
            // 关于ToolStripMenuItem
            // 
            this.关于ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuWebsite,
            this.toolStripMenuItem1,
            this.menuAbout});
            this.关于ToolStripMenuItem.Name = "关于ToolStripMenuItem";
            this.关于ToolStripMenuItem.Size = new System.Drawing.Size(74, 24);
            this.关于ToolStripMenuItem.Text = "关于(&A)";
            // 
            // menuWebsite
            // 
            this.menuWebsite.Name = "menuWebsite";
            this.menuWebsite.Size = new System.Drawing.Size(177, 26);
            this.menuWebsite.Text = "作者网站(&W)";
            this.menuWebsite.Click += new System.EventHandler(this.MenuWebsite_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(174, 6);
            // 
            // menuAbout
            // 
            this.menuAbout.Name = "menuAbout";
            this.menuAbout.Size = new System.Drawing.Size(177, 26);
            this.menuAbout.Text = "关于...(&A)";
            this.menuAbout.Click += new System.EventHandler(this.MenuAbout_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statColor,
            this.toolStripStatusLabel1,
            this.statLabCordinate});
            this.statusStrip1.Location = new System.Drawing.Point(0, 724);
            this.statusStrip1.Margin = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(978, 26);
            this.statusStrip1.TabIndex = 5;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // statColor
            // 
            this.statColor.ForeColor = System.Drawing.Color.Black;
            this.statColor.Name = "statColor";
            this.statColor.Size = new System.Drawing.Size(148, 20);
            this.statColor.Text = "当前颜色：#000000";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(702, 20);
            this.toolStripStatusLabel1.Spring = true;
            // 
            // statLabCordinate
            // 
            this.statLabCordinate.Name = "statLabCordinate";
            this.statLabCordinate.Size = new System.Drawing.Size(113, 20);
            this.statLabCordinate.Text = "当前坐标: (0, 0)";
            // 
            // glCanvas
            // 
            this.glCanvas.DrawFPS = false;
            this.glCanvas.FrameRate = 30;
            this.glCanvas.Location = new System.Drawing.Point(180, 28);
            this.glCanvas.Margin = new System.Windows.Forms.Padding(0);
            this.glCanvas.Name = "glCanvas";
            this.glCanvas.OpenGLVersion = SharpGL.Version.OpenGLVersion.OpenGL4_0;
            this.glCanvas.RenderContextType = SharpGL.RenderContextType.DIBSection;
            this.glCanvas.RenderTrigger = SharpGL.RenderTrigger.TimerBased;
            this.glCanvas.Size = new System.Drawing.Size(800, 700);
            this.glCanvas.TabIndex = 6;
            this.glCanvas.OpenGLInitialized += new System.EventHandler(this.GlCanvas_OpenGLInitialized);
            this.glCanvas.MouseDown += new System.Windows.Forms.MouseEventHandler(this.glCanvas_MouseDown);
            this.glCanvas.MouseMove += new System.Windows.Forms.MouseEventHandler(this.glCanvas_MouseMove);
            this.glCanvas.MouseUp += new System.Windows.Forms.MouseEventHandler(this.glCanvas_MouseUp);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(978, 750);
            this.Controls.Add(this.glCanvas);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.panelTools);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "MainForm";
            this.Text = "FPainter";
            this.panelTools.ResumeLayout(false);
            this.panelTools.PerformLayout();
            this.grpToolSetting.ResumeLayout(false);
            this.grpToolSetting.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picColorYellow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorGreen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorCustom)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorRed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorBlack)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorBlue)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.glCanvas)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ColorDialog colorPicker;
        private System.Windows.Forms.RadioButton radPointer;
        private System.Windows.Forms.RadioButton radLine;
        private System.Windows.Forms.Panel panelTools;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 文件ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关于ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuNew;
        private System.Windows.Forms.ToolStripMenuItem menuClose;
        private System.Windows.Forms.ToolStripMenuItem menuWebsite;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem menuAbout;
        private System.Windows.Forms.RadioButton radEraser;
        private System.Windows.Forms.RadioButton radPolygon;
        private System.Windows.Forms.RadioButton radPencil;
        private System.Windows.Forms.RadioButton radRectangle;
        private System.Windows.Forms.RadioButton radCircle;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.GroupBox grpToolSetting;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel statLabCordinate;
        private System.Windows.Forms.Button btnColorPicker;
        private System.Windows.Forms.PictureBox picColorCustom;
        private System.Windows.Forms.PictureBox picColorRed;
        private System.Windows.Forms.PictureBox picColorBlue;
        private System.Windows.Forms.PictureBox picColorBlack;
        private System.Windows.Forms.ToolStripStatusLabel statColor;
        private System.Windows.Forms.Label labWidth;
        private System.Windows.Forms.TrackBar trackWidth;
        private System.Windows.Forms.PictureBox picColorYellow;
        private System.Windows.Forms.PictureBox picColorGreen;
        private SharpGL.OpenGLControl glCanvas;
    }
}

