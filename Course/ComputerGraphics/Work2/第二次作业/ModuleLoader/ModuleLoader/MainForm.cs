// USING OPENGL
using SharpGL;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace ModuleLoader
{

    public partial class MainForm : Form
    {
        struct Cordinate
        {
            public float x;
            public float y;
            public float z;
            public Cordinate(float _x, float _y, float _z)
            {
                x = _x;
                y = _y;
                z = _z;
            }
        }
        struct Surface
        {
            public int p1;
            public int p2;
            public int p3;
            public int p4;
            public Surface(int _p1, int _p2, int _p3, int _p4)
            {
                p1 = _p1;
                p2 = _p2;
                p3 = _p3;
                p4 = _p4;
            }
        }
        private OpenGL gl;
        private Stopwatch sw = new Stopwatch(); //计时器
        private List<Cordinate> cordinates = new List<Cordinate>();
        private List<Surface> surfaces = new List<Surface>();


        //基本配置
        float[] LightPosition;
        double[] LookAtMatrix;
        private bool dataLoaded = false;
        private bool changeDetecter = false;
        public MainForm()
        {
            InitializeComponent();
            Log("Launched.");
            Log("Made by Bill Chen (10185101210), East China Normal University.");
            Log("Note: Module file 1.dat and 2.txt should be placed in the same folder with the program.");
            Log("Initializing OpenGL...");
            Initialize();
            ClearAll();
            syncInput();
            changeDetecter = true;
            Log();
        }
        private void Log(String logContent = "Done.")
        {
            if (chkLog.Checked)
            {
                txtLog.AppendText(DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss.ff") + " " + logContent + "\r\n");
            }

        }


        //加载数据
        private void LoadData()
        {
            string line;
            System.IO.StreamReader surfaceInfoFile = new System.IO.StreamReader("1.dat");
            System.IO.StreamReader dotsCordinateFile = new System.IO.StreamReader("2.txt");
            while ((line = surfaceInfoFile.ReadLine()) != null)
            {
                string[] temp = Regex.Split(line, "\\s+");
                if (temp.Length == 6)
                {
                    surfaces.Add(new Surface(int.Parse(temp[2]), int.Parse(temp[3]),
                        int.Parse(temp[4]), int.Parse(temp[5])));
                }

            }
            while ((line = dotsCordinateFile.ReadLine()) != null)
            {
                string[] temp = Regex.Split(line, "\\s+");
                cordinates.Add(new Cordinate(float.Parse(temp[2]), float.Parse(temp[3]), float.Parse(temp[4])));
            }
            surfaceInfoFile.Close();
            dotsCordinateFile.Close();
        }

        private void Initialize()
        {
            gl = glCanvas.OpenGL;
            LookAtMatrix = new double[9] { 200, 200, 200, -30, 20, 0, 0, 12, 0 };
            LightPosition = new float[4] { 7.5f, 20f, 20f, 1f };
            chkAmbient.Checked = false;
            chkAxis.Checked = false;
            chkDiffuse.Checked = false;
            chkDots.Checked = false;
            chkSpecular.Checked = false;
            chkSurface.Checked = false;
            chkRotate.Checked = false;
            chkRepaint.Checked = true;
            gl.Disable(OpenGL.GL_LIGHTING);
            //抗锯齿和混合
            gl.Enable(OpenGL.GL_BLEND);
            gl.BlendFunc(OpenGL.GL_SRC_ALPHA, OpenGL.GL_ONE_MINUS_SRC_ALPHA);
            gl.Enable(OpenGL.GL_LINE_SMOOTH);
            gl.Enable(OpenGL.GL_POLYGON_SMOOTH);
        }

        //绘制坐标轴
        private void RenderAxis()
        {

            Log("Rendering axis... (Arrow indicates the positive direction of each axis)");
            gl.Disable(OpenGL.GL_LIGHTING);
            gl.Color(1f, 1f, 1f);
            gl.Begin(OpenGL.GL_LINES);
            {
                gl.Vertex(-100f, 0f, 0f);
                gl.Vertex(100f, 0f, 0f);
                gl.Vertex(20f, 0f, 0f);
                gl.Vertex(19f, 0.5f, 0f);
                gl.Vertex(19f, -0.5f, 0f);
                gl.Vertex(20f, 0f, 0f);

            }
            gl.End();
            gl.Begin(OpenGL.GL_LINES);
            {
                gl.Vertex(0f, -100f, 0f);
                gl.Vertex(0f, 100f, 0f);
                gl.Vertex(0f, 20f, 0f);
                gl.Vertex(0f, 19f, 0.5f);
                gl.Vertex(0f, 19f, -0.5f);
                gl.Vertex(0f, 20f, 0f);
            }
            gl.End();
            gl.Begin(OpenGL.GL_LINES);
            {
                gl.Vertex(0f, 0f, -100f);
                gl.Vertex(0f, 0f, 100f);
                gl.Vertex(0f, 0f, 20f);
                gl.Vertex(0.5f, 0f, 19f);
                gl.Vertex(-0.5f, 0f, 19f);
                gl.Vertex(0f, 0f, 20f);
            }
            gl.End();
        }

        //绘制点云
        private void RenderDots()
        {
            Log("Rendering dots...");
            gl.Color(1f, 1f, 1f);
            gl.PointSize(2.0f);
            gl.Begin(OpenGL.GL_POINTS);
            {
                foreach (Cordinate c in cordinates)
                {
                    gl.Vertex(c.x, c.y, c.z);

                }
            }
            gl.End();
        }
        private void LightConfiguration()
        {
            Log("Configuring light and materials...");
            // 光照配置和材质配置
            float[] AmbientLight = new float[4] { 0.5f, 1f, 1f, 1f };
            float[] DiffuseLight = new float[4] { 0.5f, 1f, 1f, 1f };
            float[] SpecularLight = new float[4] { 1f, 1f, 1f, 1f };

            float[] modelMaterial = new float[4] { 0.3f, 0.3f, 0.35f, 1f };
            float[] modelSpecularSet = new float[4] { 0.5f, 1.0f, 1.0f, 1.0f };

            if (chkAmbient.Checked || chkDiffuse.Checked || chkSpecular.Checked)
            {
                // 绘制光源
                gl.PointSize(5f);
                gl.Begin(OpenGL.GL_POINTS);
                {
                    gl.Vertex(LightPosition[0], LightPosition[1], LightPosition[2]);
                }
                gl.End();
                gl.PointSize(2);
            }

            gl.Enable(OpenGL.GL_LIGHTING);
            gl.Enable(OpenGL.GL_LIGHT0);
            gl.Enable(OpenGL.GL_LIGHT1);
            gl.Enable(OpenGL.GL_LIGHT2);
            if (chkAmbient.Checked)
            {
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_AMBIENT, AmbientLight);
            }
            else
            {
                gl.Disable(OpenGL.GL_LIGHT0);
            }
            if (chkDiffuse.Checked)
            {
                gl.Light(OpenGL.GL_LIGHT1, OpenGL.GL_DIFFUSE, DiffuseLight);
            }
            else
            {
                gl.Disable(OpenGL.GL_LIGHT1);
            }
            if (chkSpecular.Checked)
            {
                gl.Light(OpenGL.GL_LIGHT2, OpenGL.GL_SPECULAR, SpecularLight);
                gl.Material(OpenGL.GL_FRONT, OpenGL.GL_SPECULAR, modelSpecularSet);
                gl.Material(OpenGL.GL_FRONT, OpenGL.GL_SHININESS, 64f);
            }
            else
            {

                gl.Material(OpenGL.GL_FRONT, OpenGL.GL_SHININESS, 0f);
                gl.Disable(OpenGL.GL_LIGHT2);
            }
            // gl.Material(OpenGL.GL_FRONT, OpenGL.GL_DIFFUSE, modelMaterial);
            // gl.Material(OpenGL.GL_FRONT, OpenGL.GL_AMBIENT, modelMaterial);
            gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_POSITION, LightPosition);
            gl.Light(OpenGL.GL_LIGHT1, OpenGL.GL_POSITION, LightPosition);
            gl.Light(OpenGL.GL_LIGHT2, OpenGL.GL_POSITION, LightPosition);

        }
        
        //绘制边
        private void RenderSurfaces()
        {
            gl.Enable(OpenGL.GL_DEPTH_TEST);
            Log("Rendering surfaces...");
            foreach (Surface s in surfaces)
            {
                gl.Begin(OpenGL.GL_POLYGON);
                {
                    gl.Vertex(cordinates[s.p1 - 1].x, cordinates[s.p1 - 1].y, cordinates[s.p1 - 1].z);
                    gl.Vertex(cordinates[s.p2 - 1].x, cordinates[s.p2 - 1].y, cordinates[s.p2 - 1].z);
                    gl.Vertex(cordinates[s.p3 - 1].x, cordinates[s.p3 - 1].y, cordinates[s.p3 - 1].z);
                    if (s.p4 != 0)
                    {
                        gl.Vertex(cordinates[s.p4 - 1].x, cordinates[s.p4 - 1].y, cordinates[s.p4 - 1].z);
                    }
                }
                gl.End();
            }

        }

        //清除所有信息并设置背景色
        private void ClearAll()
        {
            gl.ClearColor(0.3f, 0.4f, 0.5f, 1f);
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
        }

        //更新各个文本框的数值
        private void syncInput()
        {
            lightX.Value = (decimal)LightPosition[0];
            lightY.Value = (decimal)LightPosition[1];
            lightZ.Value = (decimal)LightPosition[2];

            eyeX.Value = (decimal)LookAtMatrix[0];
            eyeY.Value = (decimal)LookAtMatrix[1];
            eyeZ.Value = (decimal)LookAtMatrix[2];
            centerX.Value = (decimal)LookAtMatrix[3];
            centerY.Value = (decimal)LookAtMatrix[4];
            centerZ.Value = (decimal)LookAtMatrix[5];
            upX.Value = (decimal)LookAtMatrix[6];
            upY.Value = (decimal)LookAtMatrix[7];
            upZ.Value = (decimal)LookAtMatrix[8];
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            changeDetecter = false;
            Initialize();
            syncInput();
            sw.Restart();
            Log("Clearing openGLControl...");
            ClearAll();
            Log("Reset completed. Time used: " + sw.ElapsedMilliseconds + " ms");
            sw.Stop();
            changeDetecter = true;
        }

        private void RENDER()
        {
            if (changeDetecter)
            {
                sw.Restart();
            }
            if (!dataLoaded)
            {
                Log("Loading surface and dots data...");
                LoadData();
                Log("Data loaded successfully.");
                dataLoaded = true;
            }

            //改变视角
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadIdentity();
            gl.Perspective(30f, (double)glCanvas.Width / (double)glCanvas.Height, 3, 20000);
            gl.LookAt(LookAtMatrix[0], LookAtMatrix[1], LookAtMatrix[2],
                    LookAtMatrix[3], LookAtMatrix[4], LookAtMatrix[5],
                    LookAtMatrix[6], LookAtMatrix[7], LookAtMatrix[8]);
            gl.MatrixMode(OpenGL.GL_MODELVIEW);
            if (chkRepaint.Checked)
            {
                ClearAll();
            }

            if (chkAxis.Checked)
            {
                RenderAxis();
            }

            if (chkDots.Checked)
            {
                RenderDots();
            }
            LightConfiguration();
            if (chkSurface.Checked)
            {
                RenderSurfaces();
            }
            Log("Done. Time used: " + sw.ElapsedMilliseconds + " ms");
            sw.Stop();
        }
        private void openGLControl1_Load(object sender, EventArgs e)
        {

        }

        private void btnRenderSurfaces_Click(object sender, EventArgs e)
        {
            sw.Restart();
            changeDetecter = false;
            chkAmbient.Checked = true;
            chkAxis.Checked = true;
            chkDiffuse.Checked = true;
            chkDots.Checked = false;
            chkSpecular.Checked = true;
            chkSurface.Checked = true;
            gl.Disable(OpenGL.GL_LIGHTING);
            RENDER();
            changeDetecter = true;
        }

        private void btnRenderAll_Click(object sender, EventArgs e)
        {
            sw.Restart();
            changeDetecter = false;
            chkAmbient.Checked = true;
            chkAxis.Checked = true;
            chkDiffuse.Checked = true;
            chkDots.Checked = true;
            chkSpecular.Checked = true;
            chkSurface.Checked = true;
            changeDetecter = true;
            RENDER();
        }
        private void btnRenderDots_Click(object sender, EventArgs e)
        {
            sw.Restart();
            changeDetecter = false;
            chkAmbient.Checked = false;
            chkAxis.Checked = true;
            chkDiffuse.Checked = false;
            chkDots.Checked = true;
            chkSpecular.Checked = false;
            chkSurface.Checked = false;
            gl.Disable(OpenGL.GL_LIGHTING);
            changeDetecter = true;
            RENDER();
        }
        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        #region 繁琐而重复的配置片段
        private void lightX_ValueChanged(object sender, EventArgs e)
        {
            LightPosition[0] = (float)lightX.Value;
            if (changeDetecter)
            {
                RENDER();
            }

        }

        private void lightY_ValueChanged(object sender, EventArgs e)
        {
            LightPosition[1] = (float)lightY.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void lightZ_ValueChanged(object sender, EventArgs e)
        {
            LightPosition[2] = (float)lightZ.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void eyeX_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[0] = (float)eyeX.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void eyeY_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[1] = (float)eyeY.Value;
            if (changeDetecter)
            {
                RENDER();
            }

        }

        private void eyeZ_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[2] = (float)eyeZ.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void centerX_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[3] = (float)centerX.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void centerY_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[4] = (float)centerY.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void centerZ_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[5] = (float)centerZ.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void upX_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[6] = (float)upX.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void upY_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[7] = (float)upY.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void upZ_ValueChanged(object sender, EventArgs e)
        {
            LookAtMatrix[8] = (float)upZ.Value;
            if (changeDetecter)
            {
                RENDER();
            }
        }


        private void chkSurface_CheckedChanged(object sender, EventArgs e)
        {
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void chkDots_CheckedChanged(object sender, EventArgs e)
        {
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void chkAxis_CheckedChanged(object sender, EventArgs e)
        {
            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void chkAmbient_CheckedChanged(object sender, EventArgs e)
        {

            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void chkDiffuse_CheckedChanged(object sender, EventArgs e)
        {

            if (changeDetecter)
            {
                RENDER();
            }
        }

        private void chkEmission_CheckedChanged(object sender, EventArgs e)
        {
            if (changeDetecter)
            {
                RENDER();
            }
        }
        #endregion
        private void btnAbout_Click(object sender, EventArgs e)
        {

            chkLog.Checked = true;
            Log("===================== ABOUT =============================");
            Log("A module loader made with C# and OpenGL (SharpGL).");
            Log("Made By Bill Chen(10185101210), 2019.12.1");
            Log("GitHub: @BillChen2000");
            Log("Tutor: 王长波");
            Log("=========================================================");
            chkLog.Checked = false;
        }

        private void chkRepaint_CheckedChanged(object sender, EventArgs e)
        {
            Log("Clear before repaint: " + (chkRepaint.Checked == true ? "Enabled." : "Disabled."));
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            changeDetecter = false;
            Log("Window resized. OpenGL will reinitialize.");
            Initialize();
            ClearAll();
            changeDetecter = true;
        }



        //自动旋转
        private void timerRotation_Tick(object sender, EventArgs e)
        {
            gl.Rotate(0f, 1f, 0f);
            RENDER();
        }

        private void chkRotate_CheckedChanged(object sender, EventArgs e)
        {
            Log("Auto Rotation: " + (chkRotate.Checked == true ? "Enabled." : "Disabled."));
            timerRotation.Enabled = chkRotate.Checked;
            
        }
    }
}
