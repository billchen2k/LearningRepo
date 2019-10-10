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
        public SharpGL.OpenGL gl;                   // SharpGL包装的OpenGL
        private double fx;
        private double fy;
        private Tools selectedTool;                 //当前选择的工具
        private bool isDrawing = false;
        private Queue<fPoint> pointQueue;           //用于记录上一个点的位置

        private uint[] buffers;                     //OpenGL缓存（未实现）
        private bool toClearPoly = false;           // 多边形工具是否双击结束绘制的flag
        public Painter(OpenGL glCanvas)
        {
            gl = glCanvas;
            selectedTool = Tools.pointer;
            pointQueue = new Queue<fPoint>();
            gl.Color(0, 0, 0);
            gl.LineWidth(2);
            gl.PointSize(2);
            //初始化坐标0, 0至左上角,Translate参数经尝试得到
            gl.LoadIdentity();
            gl.Translate(-4.68f, 4.11f, -10f);
            buffers = new uint[100];
        }

   
        public void SetTool(Tools newTool)
        {
            this.selectedTool = newTool;
        }

        //设置抗锯齿开关（实验性）
        //开启后在画圆时会出问题
        public void setSmooth(bool value)
        {
            if(value == true)
            {
                gl.Enable(OpenGL.GL_BLEND);
                gl.BlendFunc(OpenGL.GL_SRC_ALPHA, OpenGL.GL_ONE_MINUS_SRC_ALPHA);
                gl.Enable(OpenGL.GL_POINT_SMOOTH);
                gl.Enable(OpenGL.GL_LINE_SMOOTH);
                gl.Enable(OpenGL.GL_POLYGON_SMOOTH);
            }
            else
            {
                gl.Disable(OpenGL.GL_BLEND);
                gl.Disable(OpenGL.GL_POINT_SMOOTH);
                gl.Disable(OpenGL.GL_LINE_SMOOTH);
                gl.Disable(OpenGL.GL_POLYGON_SMOOTH);
            }
        }

        public void SetWidth(int width)
        {
            gl.PointSize(width);
            gl.LineWidth(width);
        }

        public void SetColor(System.Drawing.Color color)
        {
            gl.Color(color.R / 255.0, color.G / 255.0, color.B / 255.0);
        }
        
        //将鼠标位置的像素数据转换为 OpenGL 坐标系中的点
        public double[] SetCordinate(int X, int Y)
        {
            this.mouseX = X;
            this.mouseY = Y; 
            fx = (double)mouseX * 9.36 / 800.0;
            fy = -(double)mouseY * 8.22 / 700.0;
            double[] result = { fx, fy };
            return result;
        }

        //新建画布
        public void Clear()
        {
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
        }

        //在鼠标按下的时候触发的事件
        public void DrawStart()
        {
            fPoint currentPoint = new fPoint(fx, fy);
            switch (selectedTool)
            {
                case Tools.pointer:
                    break;
                //橡皮擦为白色的50宽度的铅笔
                case Tools.pen:
                case Tools.eraser:
                    pointQueue.Enqueue(currentPoint);
                    gl.Begin(OpenGL.GL_POINTS);
                    {
                        gl.Vertex(fx, fy, 0f);
                    }
                    gl.End();
                    gl.Flush();
                    break;
                case Tools.line:
                    pointQueue.Enqueue(currentPoint);
                    //gl.genbuffers(1, buffers);
                    //gl.bindbuffer(buffers[0], opengl.gl_color_buffer_bit);
                    break;
                case Tools.circle:
                case Tools.rec:
                    pointQueue.Enqueue(currentPoint);
                    break;
                case Tools.poly:
                    if(pointQueue.Count != 0)
                    {
                        
                        gl.Begin(OpenGL.GL_LINES);
                        {
                            gl.Vertex(currentPoint.fx, currentPoint.fy, 0f);
                            gl.Vertex(pointQueue.Peek().fx, pointQueue.Peek().fy);
                        }
                        gl.End();
                        pointQueue.Clear();
                    }
                    break;

            }
            isDrawing = true;
        }
        
        //在鼠标抬起时触发的事件
        //通过读取 pointQueue 内的上一个点的数据连线
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
                case Tools.circle:
                    //使用参数函数 x = Acos; y = Bsin画椭圆
                    double lenA = Math.Abs(fx - pointQueue.Peek().fx) / 2.0;
                    double lenB = Math.Abs(fy - pointQueue.Peek().fy) / 2.0;
                    fPoint center = new fPoint((fx + pointQueue.Peek().fx) / 2.0, (fy + pointQueue.Peek().fy) / 2.0);
                    int n = 90;        //精度，以n边的多边形代替椭圆
                    gl.Begin(OpenGL.GL_POLYGON);
                    {
                        for (double alpha = 0; alpha < Math.PI * 2; alpha += Math.PI / n) 
                        {
                            gl.Vertex(center.fx + Math.Cos(alpha) * lenA, center.fy + Math.Sin(alpha) * lenB, 0f);
                        }
                    }
                    gl.End();
                    pointQueue.Clear();
                    break;
                case Tools.rec:
                    gl.Begin(OpenGL.GL_POLYGON);
                    {
                        gl.Vertex(fx, fy, 0f);
                        gl.Vertex(fx, pointQueue.Peek().fy, 0f);
                        gl.Vertex(pointQueue.Peek().fx, pointQueue.Peek().fy, 0f);
                        gl.Vertex(pointQueue.Peek().fx, fy, 0f);
                    }
                    gl.End();
                    pointQueue.Clear();
                    break;
                case Tools.poly:
                    //检测是否刚刚双击
                    if(!toClearPoly)
                        pointQueue.Enqueue(new fPoint(fx, fy));
                    else
                    {
                        pointQueue.Clear();
                        toClearPoly = false;
                    }
                    break;
            }
        }

        //鼠标拖动中触发的事件，主要用于铅笔与橡皮擦
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
                    case Tools.circle:
                    case Tools.poly:
                        break;
                }
            }
        }
        
        public void ClearPoly()
        {
            toClearPoly = true;
            pointQueue.Clear();
        }
    }
}
