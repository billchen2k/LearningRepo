using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SharpGL;

namespace FPainter
{
    public partial class MainForm : Form
    {
        Painter painter;
        private Color tempColor;
        private int tempWidth;
        public MainForm()
        {
           
            InitializeComponent();
            painter = new Painter(glCanvas.OpenGL);
        }


        private void MenuAbout_Click(object sender, EventArgs e)
        {
            MessageBox.Show(this,
                            "FPainter 1.0\n一个基于 C# 和 OpenGL 的简易画图软件。\n\n作者：Bill Chen\nGitHub: @Flento\nTutor: 王长波\n\n2019.10, East China Normal University",
                            "关于 FPainter",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
        }

        private void MenuWebsite_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://billc.io");
        }

        private void MenuClose_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show(this,
                                "确认退出吗？",
                                "提示",
                                MessageBoxButtons.OKCancel,
                                MessageBoxIcon.Question) == DialogResult.OK)
            {
                Application.Exit();
            }
           
        }

        private void GlCanvas_OpenGLInitialized(object sender, EventArgs e)
        {
            OpenGL gl = glCanvas.OpenGL;
            gl.ClearColor(1,1,1,0);
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
         
        }

        #region --- 几个工具选项的设置部分 ---
        private void radPolygon_CheckedChanged(object sender, EventArgs e)
        {
            painter.SetTool(Tools.poly);
            glCanvas.Cursor = Cursors.Cross;
        }

        private void radRectangle_CheckedChanged(object sender, EventArgs e)
        {
            painter.SetTool(Tools.rec);
            glCanvas.Cursor = Cursors.Cross;
        }

        private void radPointer_CheckedChanged(object sender, EventArgs e)
        {
            painter.SetTool(Tools.pointer);
            glCanvas.Cursor = Cursors.Arrow;
        }

        private void radPencil_CheckedChanged(object sender, EventArgs e)
        {
            painter.SetTool(Tools.pen);
            glCanvas.Cursor = Cursors.Cross;
        }

        private void radEraser_CheckedChanged(object sender, EventArgs e)
        {
            if (radEraser.Checked)
            {
                painter.SetTool(Tools.eraser);
                tempColor = statColor.ForeColor;
                tempWidth = trackWidth.Value;
                setColor(Color.White);
                trackWidth.Value = 50;
                trackWidth_Scroll(this, e);
                glCanvas.Cursor = Cursors.Cross;
            }
            else
            {
                setColor(tempColor);
                trackWidth.Value = tempWidth;
                trackWidth_Scroll(this, e);
            }

        }
        
        private void radLine_CheckedChanged(object sender, EventArgs e)
        {
            painter.SetTool(Tools.line);
            glCanvas.Cursor = Cursors.Cross;
        }

        private void radCircle_CheckedChanged(object sender, EventArgs e)
        {
            painter.SetTool(Tools.circle);
        }
        #endregion

        #region --- 几个颜色按钮的设置部分 ---

        private void picColorBlack_Click(object sender, EventArgs e)
        {
            setColor(picColorBlack.BackColor);
        }

        private void picColorBlue_Click(object sender, EventArgs e)
        {
            setColor(picColorBlue.BackColor);

        }

        private void picColorRed_Click(object sender, EventArgs e)
        {
            setColor(picColorRed.BackColor);
        }

        private void picColorGreen_Click(object sender, EventArgs e)
        {
            setColor(picColorGreen.BackColor);
        }

        private void picColorYellow_Click(object sender, EventArgs e)
        {
            setColor(picColorYellow.BackColor);
        }

        private void picColorCustom_Click(object sender, EventArgs e)
        {
            setColor(picColorCustom.BackColor);
        }
        #endregion

        private void glCanvas_MouseDown(object sender, MouseEventArgs e)
        {
            painter.DrawStart();

        }

        private void glCanvas_MouseUp(object sender, MouseEventArgs e)
        {
            painter.DrawEnd();
        }
        private void glCanvas_MouseMove(object sender, MouseEventArgs e)
        {
            int mouseX = (int)glCanvas.PointToClient(Control.MousePosition).X;
            int mouseY = (int)glCanvas.PointToClient(Control.MousePosition).Y;
            painter.SetCordinate(mouseX, mouseY);
            statLabCordinate.Text = "当前坐标：（" + mouseX.ToString() + ", " + mouseY.ToString() + "）";
            painter.DrawDoing();
        }

        private void trackWidth_Scroll(object sender, EventArgs e)
        {
            painter.SetWidth(trackWidth.Value);
            labWidth.Text = "粗细（" + trackWidth.Value.ToString() + "px）";
        }

        private void btnColorPicker_Click(object sender, EventArgs e)
        {
            colorPicker.ShowDialog();
            picColorCustom.BackColor = colorPicker.Color;
            this.setColor(colorPicker.Color);
        }

        private void setColor(Color color)
        {
            statColor.Text = "当前颜色：" + Utils.ToHexColor(color);
            statColor.ForeColor = color;
            painter.setColor(color);
        }

        private void menuNew_Click(object sender, EventArgs e)
        {
            painter.Clear();
            setColor(Color.Black);
            trackWidth.Value = 2;
            trackWidth_Scroll(this, e);
            radPointer.Checked = true;
        }
    }

}
