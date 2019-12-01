namespace ModuleLoader
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
            this.RenderController = new SharpDX.Windows.RenderControl();
            this.btnRenderDots = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.btnRenderSurfaces = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.txtLog = new System.Windows.Forms.TextBox();
            this.openGLControl1 = new SharpGL.OpenGLControl();
            ((System.ComponentModel.ISupportInitialize)(this.openGLControl1)).BeginInit();
            this.SuspendLayout();
            // 
            // RenderController
            // 
            this.RenderController.Location = new System.Drawing.Point(0, 0);
            this.RenderController.Margin = new System.Windows.Forms.Padding(0);
            this.RenderController.Name = "RenderController";
            this.RenderController.Size = new System.Drawing.Size(1260, 700);
            this.RenderController.TabIndex = 0;
            // 
            // btnRenderDots
            // 
            this.btnRenderDots.Location = new System.Drawing.Point(718, 716);
            this.btnRenderDots.Name = "btnRenderDots";
            this.btnRenderDots.Size = new System.Drawing.Size(176, 31);
            this.btnRenderDots.TabIndex = 1;
            this.btnRenderDots.Text = "Render Dots";
            this.btnRenderDots.UseVisualStyleBackColor = true;
            this.btnRenderDots.Click += new System.EventHandler(this.btnRenderDots_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(24, 723);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(523, 27);
            this.label1.TabIndex = 0;
            this.label1.Text = "Note: Module file 1.dat and 2.txt should be placed in the same folder with the pr" +
    "ogram.";
            // 
            // btnRenderSurfaces
            // 
            this.btnRenderSurfaces.Location = new System.Drawing.Point(900, 716);
            this.btnRenderSurfaces.Name = "btnRenderSurfaces";
            this.btnRenderSurfaces.Size = new System.Drawing.Size(173, 31);
            this.btnRenderSurfaces.TabIndex = 1;
            this.btnRenderSurfaces.Text = "Render Surfaces";
            this.btnRenderSurfaces.UseVisualStyleBackColor = true;
            // 
            // btnReset
            // 
            this.btnReset.Location = new System.Drawing.Point(1079, 716);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(173, 31);
            this.btnReset.TabIndex = 1;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // txtLog
            // 
            this.txtLog.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.txtLog.Location = new System.Drawing.Point(0, 758);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ReadOnly = true;
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtLog.Size = new System.Drawing.Size(1260, 109);
            this.txtLog.TabIndex = 2;
            // 
            // openGLControl1
            // 
            this.openGLControl1.DrawFPS = false;
            this.openGLControl1.Location = new System.Drawing.Point(0, 0);
            this.openGLControl1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.openGLControl1.Name = "openGLControl1";
            this.openGLControl1.OpenGLVersion = SharpGL.Version.OpenGLVersion.OpenGL2_1;
            this.openGLControl1.RenderContextType = SharpGL.RenderContextType.DIBSection;
            this.openGLControl1.RenderTrigger = SharpGL.RenderTrigger.TimerBased;
            this.openGLControl1.Size = new System.Drawing.Size(1260, 700);
            this.openGLControl1.TabIndex = 4;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1258, 866);
            this.Controls.Add(this.openGLControl1);
            this.Controls.Add(this.txtLog);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnRenderSurfaces);
            this.Controls.Add(this.btnRenderDots);
            this.Controls.Add(this.RenderController);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "MainForm";
            this.Text = "Module Loader";
            ((System.ComponentModel.ISupportInitialize)(this.openGLControl1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private SharpDX.Windows.RenderControl RenderController;
        private System.Windows.Forms.Button btnRenderDots;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnRenderSurfaces;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.TextBox txtLog;
        private SharpGL.OpenGLControl openGLControl1;
    }
}

