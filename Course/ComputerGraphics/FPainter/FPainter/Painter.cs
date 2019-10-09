using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpGL;
enum Tools
{
    pointer,
    pen,
    eraser,
    line,
    circle,
    rec,
    poly
}

public struct fPoint
{
    public double fx;
    public double fy;
    public fPoint(double x, double y)
    {
        fx = x;
        fy = y;
    }
}
namespace FPainter
{
    class Painter
    {
        public int mouseX = 0;
        public int mouseY = 0;
        public SharpGL.OpenGL gl;
        private double fx;
        private double fy;
        private Tools selectedTool;
        private bool isDrawing = false;
        private Queue<fPoint> pointQueue;
        // 帧缓冲区，用于预览绘制的直线
        private uint[] buffers;
        public Painter(OpenGL glCanvas)
        {
            gl = glCanvas;
            selectedTool = Tools.pointer;
            pointQueue = new Queue<fPoint>();
            gl.Color(0, 0, 0);
            gl.LineWidth(2);
            gl.PointSize(2);
            gl.LoadIdentity();
            gl.Translate(-4.68f, 4.11f, -10f);
            buffers = new uint[100];
        }

        public void SetTool(Tools newTool)
        {
            this.selectedTool = newTool;
        }

        public void SetWidth(int width)
        {
            gl.PointSize(width);
            gl.LineWidth(width);
        }

        public void setColor(System.Drawing.Color color)
        {
            gl.Color(color.R / 255.0, color.G / 255.0, color.B / 255.0);
        }
        
        public double[] SetCordinate(int X, int Y)
        {
            this.mouseX = X;
            this.mouseY = Y; 
            fx = (double)mouseX * 9.36 / 800.0;
            fy = -(double)mouseY * 8.22 / 700.0;
            double[] result = { fx, fy };
            return result;
        }

        public void Clear()
        {
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
        }
        public void DrawStart()
        {
            switch (selectedTool)
            {
                case Tools.pointer:
                    break;
                case Tools.pen:
                case Tools.eraser:
                    pointQueue.Enqueue(new fPoint(fx, fy));
                    gl.Begin(OpenGL.GL_POINTS);
                    {
                        gl.Vertex(fx, fy, 0f);

                    }
                    gl.End();
                    gl.Flush();
                    break;
                case Tools.line:
                    pointQueue.Enqueue(new fPoint(fx, fy));
                    //gl.genbuffers(1, buffers);
                    //gl.bindbuffer(buffers[0], opengl.gl_color_buffer_bit);
                    break;
            }
            isDrawing = true;
        }
        
        public void DrawEnd()
        {
            isDrawing = false;
            switch (selectedTool)
            {
                case Tools.pointer:
                    break;
                case Tools.pen:
                case Tools.eraser:
                    pointQueue.Clear();
                    break;
                case Tools.line:
                    gl.Begin(OpenGL.GL_LINES);
                    {
                        gl.Vertex(fx, fy, 0f);
                        gl.Vertex(pointQueue.Peek().fx, pointQueue.Peek().fy, 0f);
                    }
                    pointQueue.Clear();
                    gl.End();
                    break;
            }
        }

        public void DrawDoing()
        {
            if(isDrawing == true)
            {
                switch (selectedTool)
                {
                    case Tools.pointer:
                        break;
                    case Tools.pen:
                    case Tools.eraser:
                        gl.Begin(OpenGL.GL_LINES);
                        {
                            //顶点 
                            pointQueue.Enqueue(new fPoint(fx, fy));
                            gl.Vertex(fx, fy, 0f);
                            gl.Vertex(pointQueue.Peek().fx, pointQueue.Peek().fy, 0f);
                        }
                        gl.End();
                        gl.Flush();
                        pointQueue.Dequeue();
                        break;
                    case Tools.line:
                        gl.Clear(OpenGL.GL_ARRAY_BUFFER);
                        gl.Begin(OpenGL.GL_LINES);
                        {
                            gl.Vertex(fx, fy, 0f);
                            gl.Vertex(pointQueue.Peek().fx, pointQueue.Peek().fy, 0f);
                        }
                        gl.End();
                        break;
                }
            }
        }

    }
}
