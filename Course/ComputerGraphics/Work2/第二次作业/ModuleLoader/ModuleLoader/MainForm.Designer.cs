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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.btnRenderDots = new System.Windows.Forms.Button();
            this.btnRenderSurfaces = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.txtLog = new System.Windows.Forms.TextBox();
            this.glCanvas = new SharpGL.OpenGLControl();
            this.label1 = new System.Windows.Forms.Label();
            this.chkDots = new System.Windows.Forms.CheckBox();
            this.chkSurface = new System.Windows.Forms.CheckBox();
            this.chkAxis = new System.Windows.Forms.CheckBox();
            this.chkAmbient = new System.Windows.Forms.CheckBox();
            this.chkDiffuse = new System.Windows.Forms.CheckBox();
            this.chkSpecular = new System.Windows.Forms.CheckBox();
            this.eyeX = new System.Windows.Forms.NumericUpDown();
            this.eyeY = new System.Windows.Forms.NumericUpDown();
            this.eyeZ = new System.Windows.Forms.NumericUpDown();
            this.centerX = new System.Windows.Forms.NumericUpDown();
            this.centerY = new System.Windows.Forms.NumericUpDown();
            this.centerZ = new System.Windows.Forms.NumericUpDown();
            this.upX = new System.Windows.Forms.NumericUpDown();
            this.upY = new System.Windows.Forms.NumericUpDown();
            this.upZ = new System.Windows.Forms.NumericUpDown();
            this.btnRenderAll = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.lightX = new System.Windows.Forms.NumericUpDown();
            this.lightY = new System.Windows.Forms.NumericUpDown();
            this.lightZ = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.chkRepaint = new System.Windows.Forms.CheckBox();
            this.btnAbout = new System.Windows.Forms.Button();
            this.chkRotate = new System.Windows.Forms.CheckBox();
            this.timerRotation = new System.Windows.Forms.Timer(this.components);
            this.chkLog = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.glCanvas)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eyeX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eyeY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eyeZ)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.centerX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.centerY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.centerZ)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.upX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.upY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.upZ)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lightX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lightY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lightZ)).BeginInit();
            this.SuspendLayout();
            // 
            // btnRenderDots
            // 
            this.btnRenderDots.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnRenderDots.Location = new System.Drawing.Point(1191, 582);
            this.btnRenderDots.Name = "btnRenderDots";
            this.btnRenderDots.Size = new System.Drawing.Size(177, 31);
            this.btnRenderDots.TabIndex = 1;
            this.btnRenderDots.Text = "Render Dots Only";
            this.btnRenderDots.UseVisualStyleBackColor = true;
            this.btnRenderDots.Click += new System.EventHandler(this.btnRenderDots_Click);
            // 
            // btnRenderSurfaces
            // 
            this.btnRenderSurfaces.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnRenderSurfaces.Location = new System.Drawing.Point(1191, 619);
            this.btnRenderSurfaces.Name = "btnRenderSurfaces";
            this.btnRenderSurfaces.Size = new System.Drawing.Size(177, 31);
            this.btnRenderSurfaces.TabIndex = 1;
            this.btnRenderSurfaces.Text = "Render Surfaces With Light";
            this.btnRenderSurfaces.UseVisualStyleBackColor = true;
            this.btnRenderSurfaces.Click += new System.EventHandler(this.btnRenderSurfaces_Click);
            // 
            // btnReset
            // 
            this.btnReset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnReset.Location = new System.Drawing.Point(1191, 656);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(177, 31);
            this.btnReset.TabIndex = 1;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // txtLog
            // 
            this.txtLog.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtLog.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.txtLog.Location = new System.Drawing.Point(0, 738);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ReadOnly = true;
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtLog.Size = new System.Drawing.Size(1384, 134);
            this.txtLog.TabIndex = 2;
            // 
            // glCanvas
            // 
            this.glCanvas.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.glCanvas.DrawFPS = false;
            this.glCanvas.Location = new System.Drawing.Point(0, 1);
            this.glCanvas.Margin = new System.Windows.Forms.Padding(4);
            this.glCanvas.Name = "glCanvas";
            this.glCanvas.OpenGLVersion = SharpGL.Version.OpenGLVersion.OpenGL2_1;
            this.glCanvas.RenderContextType = SharpGL.RenderContextType.DIBSection;
            this.glCanvas.RenderTrigger = SharpGL.RenderTrigger.TimerBased;
            this.glCanvas.Size = new System.Drawing.Size(1170, 739);
            this.glCanvas.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1188, 193);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(104, 17);
            this.label1.TabIndex = 5;
            this.label1.Text = "glLookAt Matrix:";
            // 
            // chkDots
            // 
            this.chkDots.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkDots.AutoSize = true;
            this.chkDots.Location = new System.Drawing.Point(1191, 48);
            this.chkDots.Name = "chkDots";
            this.chkDots.Size = new System.Drawing.Size(100, 21);
            this.chkDots.TabIndex = 6;
            this.chkDots.Text = "Render Dots";
            this.chkDots.UseVisualStyleBackColor = true;
            this.chkDots.CheckedChanged += new System.EventHandler(this.chkDots_CheckedChanged);
            // 
            // chkSurface
            // 
            this.chkSurface.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkSurface.AutoSize = true;
            this.chkSurface.Location = new System.Drawing.Point(1191, 21);
            this.chkSurface.Name = "chkSurface";
            this.chkSurface.Size = new System.Drawing.Size(122, 21);
            this.chkSurface.TabIndex = 6;
            this.chkSurface.Text = "Render Surfaces";
            this.chkSurface.UseVisualStyleBackColor = true;
            this.chkSurface.CheckedChanged += new System.EventHandler(this.chkSurface_CheckedChanged);
            // 
            // chkAxis
            // 
            this.chkAxis.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkAxis.AutoSize = true;
            this.chkAxis.Location = new System.Drawing.Point(1191, 75);
            this.chkAxis.Name = "chkAxis";
            this.chkAxis.Size = new System.Drawing.Size(96, 21);
            this.chkAxis.TabIndex = 6;
            this.chkAxis.Text = "Render Axis";
            this.chkAxis.UseVisualStyleBackColor = true;
            this.chkAxis.CheckedChanged += new System.EventHandler(this.chkAxis_CheckedChanged);
            // 
            // chkAmbient
            // 
            this.chkAmbient.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkAmbient.AutoSize = true;
            this.chkAmbient.Location = new System.Drawing.Point(1191, 102);
            this.chkAmbient.Name = "chkAmbient";
            this.chkAmbient.Size = new System.Drawing.Size(150, 21);
            this.chkAmbient.TabIndex = 6;
            this.chkAmbient.Text = "Enable Ambient Light";
            this.chkAmbient.UseVisualStyleBackColor = true;
            this.chkAmbient.CheckedChanged += new System.EventHandler(this.chkAmbient_CheckedChanged);
            // 
            // chkDiffuse
            // 
            this.chkDiffuse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkDiffuse.AutoSize = true;
            this.chkDiffuse.Location = new System.Drawing.Point(1191, 129);
            this.chkDiffuse.Name = "chkDiffuse";
            this.chkDiffuse.Size = new System.Drawing.Size(142, 21);
            this.chkDiffuse.TabIndex = 6;
            this.chkDiffuse.Text = "Enable Diffuse Light";
            this.chkDiffuse.UseVisualStyleBackColor = true;
            this.chkDiffuse.CheckedChanged += new System.EventHandler(this.chkDiffuse_CheckedChanged);
            // 
            // chkSpecular
            // 
            this.chkSpecular.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkSpecular.AutoSize = true;
            this.chkSpecular.Location = new System.Drawing.Point(1191, 156);
            this.chkSpecular.Name = "chkSpecular";
            this.chkSpecular.Size = new System.Drawing.Size(152, 21);
            this.chkSpecular.TabIndex = 6;
            this.chkSpecular.Text = "Enable Specular Light";
            this.chkSpecular.UseVisualStyleBackColor = true;
            this.chkSpecular.CheckedChanged += new System.EventHandler(this.chkEmission_CheckedChanged);
            // 
            // eyeX
            // 
            this.eyeX.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.eyeX.DecimalPlaces = 1;
            this.eyeX.Increment = new decimal(new int[] {
            25,
            0,
            0,
            65536});
            this.eyeX.Location = new System.Drawing.Point(1191, 222);
            this.eyeX.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.eyeX.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.eyeX.Name = "eyeX";
            this.eyeX.Size = new System.Drawing.Size(55, 23);
            this.eyeX.TabIndex = 8;
            this.eyeX.ValueChanged += new System.EventHandler(this.eyeX_ValueChanged);
            // 
            // eyeY
            // 
            this.eyeY.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.eyeY.DecimalPlaces = 1;
            this.eyeY.Increment = new decimal(new int[] {
            25,
            0,
            0,
            65536});
            this.eyeY.Location = new System.Drawing.Point(1252, 222);
            this.eyeY.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.eyeY.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.eyeY.Name = "eyeY";
            this.eyeY.Size = new System.Drawing.Size(55, 23);
            this.eyeY.TabIndex = 8;
            this.eyeY.ValueChanged += new System.EventHandler(this.eyeY_ValueChanged);
            // 
            // eyeZ
            // 
            this.eyeZ.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.eyeZ.DecimalPlaces = 1;
            this.eyeZ.Increment = new decimal(new int[] {
            25,
            0,
            0,
            65536});
            this.eyeZ.Location = new System.Drawing.Point(1313, 222);
            this.eyeZ.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.eyeZ.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.eyeZ.Name = "eyeZ";
            this.eyeZ.Size = new System.Drawing.Size(55, 23);
            this.eyeZ.TabIndex = 8;
            this.eyeZ.ValueChanged += new System.EventHandler(this.eyeZ_ValueChanged);
            // 
            // centerX
            // 
            this.centerX.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.centerX.DecimalPlaces = 1;
            this.centerX.Increment = new decimal(new int[] {
            25,
            0,
            0,
            65536});
            this.centerX.Location = new System.Drawing.Point(1191, 276);
            this.centerX.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.centerX.Minimum = new decimal(new int[] {
            200,
            0,
            0,
            -2147483648});
            this.centerX.Name = "centerX";
            this.centerX.Size = new System.Drawing.Size(55, 23);
            this.centerX.TabIndex = 8;
            this.centerX.ValueChanged += new System.EventHandler(this.centerX_ValueChanged);
            // 
            // centerY
            // 
            this.centerY.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.centerY.DecimalPlaces = 1;
            this.centerY.Increment = new decimal(new int[] {
            25,
            0,
            0,
            65536});
            this.centerY.Location = new System.Drawing.Point(1252, 276);
            this.centerY.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.centerY.Minimum = new decimal(new int[] {
            200,
            0,
            0,
            -2147483648});
            this.centerY.Name = "centerY";
            this.centerY.Size = new System.Drawing.Size(55, 23);
            this.centerY.TabIndex = 8;
            this.centerY.ValueChanged += new System.EventHandler(this.centerY_ValueChanged);
            // 
            // centerZ
            // 
            this.centerZ.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.centerZ.DecimalPlaces = 1;
            this.centerZ.Increment = new decimal(new int[] {
            25,
            0,
            0,
            65536});
            this.centerZ.Location = new System.Drawing.Point(1313, 276);
            this.centerZ.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.centerZ.Minimum = new decimal(new int[] {
            200,
            0,
            0,
            -2147483648});
            this.centerZ.Name = "centerZ";
            this.centerZ.Size = new System.Drawing.Size(55, 23);
            this.centerZ.TabIndex = 8;
            this.centerZ.ValueChanged += new System.EventHandler(this.centerZ_ValueChanged);
            // 
            // upX
            // 
            this.upX.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.upX.DecimalPlaces = 1;
            this.upX.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.upX.Location = new System.Drawing.Point(1191, 334);
            this.upX.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.upX.Minimum = new decimal(new int[] {
            200,
            0,
            0,
            -2147483648});
            this.upX.Name = "upX";
            this.upX.Size = new System.Drawing.Size(55, 23);
            this.upX.TabIndex = 8;
            this.upX.ValueChanged += new System.EventHandler(this.upX_ValueChanged);
            // 
            // upY
            // 
            this.upY.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.upY.DecimalPlaces = 1;
            this.upY.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.upY.Location = new System.Drawing.Point(1252, 334);
            this.upY.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.upY.Minimum = new decimal(new int[] {
            200,
            0,
            0,
            -2147483648});
            this.upY.Name = "upY";
            this.upY.Size = new System.Drawing.Size(55, 23);
            this.upY.TabIndex = 8;
            this.upY.ValueChanged += new System.EventHandler(this.upY_ValueChanged);
            // 
            // upZ
            // 
            this.upZ.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.upZ.DecimalPlaces = 1;
            this.upZ.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.upZ.Location = new System.Drawing.Point(1313, 334);
            this.upZ.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.upZ.Minimum = new decimal(new int[] {
            200,
            0,
            0,
            -2147483648});
            this.upZ.Name = "upZ";
            this.upZ.Size = new System.Drawing.Size(55, 23);
            this.upZ.TabIndex = 8;
            this.upZ.ValueChanged += new System.EventHandler(this.upZ_ValueChanged);
            // 
            // btnRenderAll
            // 
            this.btnRenderAll.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnRenderAll.Location = new System.Drawing.Point(1191, 547);
            this.btnRenderAll.Name = "btnRenderAll";
            this.btnRenderAll.Size = new System.Drawing.Size(177, 29);
            this.btnRenderAll.TabIndex = 9;
            this.btnRenderAll.Text = "Render All";
            this.btnRenderAll.UseVisualStyleBackColor = true;
            this.btnRenderAll.Click += new System.EventHandler(this.btnRenderAll_Click);
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(1188, 399);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(137, 17);
            this.label2.TabIndex = 5;
            this.label2.Text = "Light Position (X, Y, Z):";
            // 
            // lightX
            // 
            this.lightX.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lightX.DecimalPlaces = 1;
            this.lightX.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.lightX.Location = new System.Drawing.Point(1191, 428);
            this.lightX.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.lightX.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
            this.lightX.Name = "lightX";
            this.lightX.Size = new System.Drawing.Size(55, 23);
            this.lightX.TabIndex = 8;
            this.lightX.ValueChanged += new System.EventHandler(this.lightX_ValueChanged);
            // 
            // lightY
            // 
            this.lightY.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lightY.DecimalPlaces = 1;
            this.lightY.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.lightY.Location = new System.Drawing.Point(1252, 428);
            this.lightY.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.lightY.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
            this.lightY.Name = "lightY";
            this.lightY.Size = new System.Drawing.Size(55, 23);
            this.lightY.TabIndex = 8;
            this.lightY.ValueChanged += new System.EventHandler(this.lightY_ValueChanged);
            // 
            // lightZ
            // 
            this.lightZ.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lightZ.DecimalPlaces = 1;
            this.lightZ.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.lightZ.Location = new System.Drawing.Point(1313, 428);
            this.lightZ.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.lightZ.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
            this.lightZ.Name = "lightZ";
            this.lightZ.Size = new System.Drawing.Size(55, 23);
            this.lightZ.TabIndex = 8;
            this.lightZ.ValueChanged += new System.EventHandler(this.lightZ_ValueChanged);
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(1204, 248);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(154, 17);
            this.label3.TabIndex = 5;
            this.label3.Text = "eyeX        eyeY        eyeZ";
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(1194, 302);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(166, 17);
            this.label4.TabIndex = 5;
            this.label4.Text = "centerX   centerY    centerZ";
            // 
            // label5
            // 
            this.label5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(1204, 360);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(155, 17);
            this.label5.TabIndex = 5;
            this.label5.Text = "upX          upY          upZ";
            // 
            // chkRepaint
            // 
            this.chkRepaint.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkRepaint.AutoSize = true;
            this.chkRepaint.Checked = true;
            this.chkRepaint.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkRepaint.Location = new System.Drawing.Point(1191, 466);
            this.chkRepaint.Name = "chkRepaint";
            this.chkRepaint.Size = new System.Drawing.Size(148, 21);
            this.chkRepaint.TabIndex = 6;
            this.chkRepaint.Text = "Clear Before Repaint";
            this.chkRepaint.UseVisualStyleBackColor = true;
            this.chkRepaint.CheckedChanged += new System.EventHandler(this.chkRepaint_CheckedChanged);
            // 
            // btnAbout
            // 
            this.btnAbout.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnAbout.Location = new System.Drawing.Point(1191, 693);
            this.btnAbout.Name = "btnAbout";
            this.btnAbout.Size = new System.Drawing.Size(177, 31);
            this.btnAbout.TabIndex = 1;
            this.btnAbout.Text = "About";
            this.btnAbout.UseVisualStyleBackColor = true;
            this.btnAbout.Click += new System.EventHandler(this.btnAbout_Click);
            // 
            // chkRotate
            // 
            this.chkRotate.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkRotate.AutoSize = true;
            this.chkRotate.Location = new System.Drawing.Point(1191, 493);
            this.chkRotate.Name = "chkRotate";
            this.chkRotate.Size = new System.Drawing.Size(150, 21);
            this.chkRotate.TabIndex = 6;
            this.chkRotate.Text = "Enable Auto Rotation";
            this.chkRotate.UseVisualStyleBackColor = true;
            this.chkRotate.CheckedChanged += new System.EventHandler(this.chkRotate_CheckedChanged);
            // 
            // timerRotation
            // 
            this.timerRotation.Interval = 1;
            this.timerRotation.Tick += new System.EventHandler(this.timerRotation_Tick);
            // 
            // chkLog
            // 
            this.chkLog.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkLog.AutoSize = true;
            this.chkLog.Checked = true;
            this.chkLog.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkLog.Location = new System.Drawing.Point(1191, 520);
            this.chkLog.Name = "chkLog";
            this.chkLog.Size = new System.Drawing.Size(118, 21);
            this.chkLog.TabIndex = 6;
            this.chkLog.Text = "Enable Logging";
            this.chkLog.UseVisualStyleBackColor = true;
            this.chkLog.CheckedChanged += new System.EventHandler(this.chkRotate_CheckedChanged);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1382, 873);
            this.Controls.Add(this.btnRenderAll);
            this.Controls.Add(this.lightZ);
            this.Controls.Add(this.upZ);
            this.Controls.Add(this.centerZ);
            this.Controls.Add(this.eyeZ);
            this.Controls.Add(this.lightY);
            this.Controls.Add(this.lightX);
            this.Controls.Add(this.upY);
            this.Controls.Add(this.upX);
            this.Controls.Add(this.centerY);
            this.Controls.Add(this.centerX);
            this.Controls.Add(this.eyeY);
            this.Controls.Add(this.eyeX);
            this.Controls.Add(this.chkLog);
            this.Controls.Add(this.chkRotate);
            this.Controls.Add(this.chkRepaint);
            this.Controls.Add(this.chkSpecular);
            this.Controls.Add(this.chkDiffuse);
            this.Controls.Add(this.chkAmbient);
            this.Controls.Add(this.chkAxis);
            this.Controls.Add(this.chkSurface);
            this.Controls.Add(this.chkDots);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.glCanvas);
            this.Controls.Add(this.txtLog);
            this.Controls.Add(this.btnAbout);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnRenderSurfaces);
            this.Controls.Add(this.btnRenderDots);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "MainForm";
            this.Text = "Module Loader";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.Resize += new System.EventHandler(this.MainForm_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.glCanvas)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eyeX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eyeY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eyeZ)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.centerX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.centerY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.centerZ)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.upX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.upY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.upZ)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lightX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lightY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lightZ)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button btnRenderDots;
        private System.Windows.Forms.Button btnRenderSurfaces;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.TextBox txtLog;
        private SharpGL.OpenGLControl glCanvas;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chkDots;
        private System.Windows.Forms.CheckBox chkSurface;
        private System.Windows.Forms.CheckBox chkAxis;
        private System.Windows.Forms.CheckBox chkAmbient;
        private System.Windows.Forms.CheckBox chkDiffuse;
        private System.Windows.Forms.CheckBox chkSpecular;
        private System.Windows.Forms.NumericUpDown eyeX;
        private System.Windows.Forms.NumericUpDown eyeY;
        private System.Windows.Forms.NumericUpDown eyeZ;
        private System.Windows.Forms.NumericUpDown centerX;
        private System.Windows.Forms.NumericUpDown centerY;
        private System.Windows.Forms.NumericUpDown centerZ;
        private System.Windows.Forms.NumericUpDown upX;
        private System.Windows.Forms.NumericUpDown upY;
        private System.Windows.Forms.NumericUpDown upZ;
        private System.Windows.Forms.Button btnRenderAll;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown lightX;
        private System.Windows.Forms.NumericUpDown lightY;
        private System.Windows.Forms.NumericUpDown lightZ;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.CheckBox chkRepaint;
        private System.Windows.Forms.Button btnAbout;
        private System.Windows.Forms.CheckBox chkRotate;
        private System.Windows.Forms.Timer timerRotation;
        private System.Windows.Forms.CheckBox chkLog;
    }
}

