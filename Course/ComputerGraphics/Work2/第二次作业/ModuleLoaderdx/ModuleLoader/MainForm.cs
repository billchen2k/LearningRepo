using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

// SharpDX References >>>

using SharpDX;
using SharpDX.Direct3D;
using SharpDX.DXGI;
using SharpDX.D3DCompiler;
using SharpDX.Windows;

using D3D11 = SharpDX.Direct3D11;



// USING OPENGL
using SharpGL;

namespace ModuleLoader
{

    public partial class MainForm : Form
    {
        Stopwatch sw = new Stopwatch();
        private D3D11.Device d3dDevice;
        private D3D11.DeviceContext d3dDeviceContext;
        private SwapChain swapChain;
        private D3D11.RenderTargetView renderTargetView;
        private Queue<Vector3> dots = new Queue<Vector3>();
        private Vector3[] dotsArray;
        private D3D11.Buffer vertexBuffer;
        private D3D11.VertexShader vertexShader;
        private D3D11.PixelShader pixelShader;

        private D3D11.InputElement[] inputElements = new D3D11.InputElement[]
        {
            new D3D11.InputElement("POSITION", 0, Format.R32G32B32A32_Float, 0)
        };
        private ShaderSignature inputSignature;
        private D3D11.InputLayout inputLayout;
        private Viewport viewport;
        public MainForm()
        {
            InitializeComponent();
            Log("Launched.");
            Log("Made by Bill Chen (10185101210), East China Normal University.");
            Log("Initializing swap chain and device context...");
            Initialize();
            Log();
        }
        private void Log(String logContent = "Done.")
        {
            txtLog.AppendText(DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss.ff") + " " + logContent +"\r\n");
        }

        private void LoadData()
        {
            dots.Enqueue(new Vector3(-0.5f,0.5f,0.0f));
            dots.Enqueue(new Vector3(0.5f, 0.5f, 0.0f));
            dots.Enqueue(new Vector3(0.0f, -0.5f, 0.0f));
            dots.Enqueue(new Vector3(.67917E+00f, .48325E+01f, .00000E+00f));
            dots.Enqueue(new Vector3(.67917E+01f, .48325E+02f, .00000E+00f));
            dots.Enqueue(new Vector3(.67917E+02f, .48325E+01f, .00000E+01f));
            dotsArray = dots.ToArray();
            vertexBuffer = D3D11.Buffer.Create<Vector3>(d3dDevice, D3D11.BindFlags.VertexBuffer, dotsArray);
        }

        private void Initialize()
        {
            ModeDescription backBufferDesc = new ModeDescription(1260, 700, new Rational(60, 1), Format.R8G8B8A8_UNorm);
            SwapChainDescription swapChainDesc = new SwapChainDescription()
            {
                ModeDescription = backBufferDesc,
                SampleDescription = new SampleDescription(1, 0),
                Usage = Usage.RenderTargetOutput,
                BufferCount = 1,
                OutputHandle = RenderController.Handle,
                IsWindowed = true
            };
            D3D11.Device.CreateWithSwapChain(DriverType.Hardware, D3D11.DeviceCreationFlags.None, 
                swapChainDesc, out d3dDevice, out swapChain);
            d3dDeviceContext = d3dDevice.ImmediateContext;
            using (D3D11.Texture2D backBuffer = swapChain.GetBackBuffer<D3D11.Texture2D>(0))
            {
                renderTargetView = new D3D11.RenderTargetView(d3dDevice, backBuffer);

            }

            // Set Viewport
            viewport = new Viewport(0, 0, 1260, 700);
            d3dDeviceContext.Rasterizer.SetViewport(viewport);
        }

        private void RenderDots()
        {
            LoadData();


            d3dDeviceContext.OutputMerger.SetRenderTargets(renderTargetView);
            d3dDeviceContext.ClearRenderTargetView(renderTargetView, new SharpDX.Color(32, 103, 178));
            swapChain.Present(1, PresentFlags.None);
            vertexBuffer = D3D11.Buffer.Create<Vector3>(d3dDevice, D3D11.BindFlags.VertexBuffer, dots.ToArray());

            //Shader Code
            using (var vertexShaderByteCode = ShaderBytecode.CompileFromFile("vertexShader.hlsl", "main", "vs_4_0", ShaderFlags.Debug))
            {
                vertexShader = new D3D11.VertexShader(d3dDevice, vertexShaderByteCode);
                inputSignature = ShaderSignature.GetInputSignature(vertexShaderByteCode);
            }
            using (var pixelShaderByteCode = ShaderBytecode.CompileFromFile("pixelShader.hlsl", "main", "ps_4_0", ShaderFlags.Debug))
            {
                pixelShader = new D3D11.PixelShader(d3dDevice, pixelShaderByteCode);
            }

            inputLayout = new D3D11.InputLayout(d3dDevice, inputSignature, inputElements);
            d3dDeviceContext.InputAssembler.InputLayout = inputLayout;
            LoadData();

            //DRAW
            d3dDeviceContext.OutputMerger.SetRenderTargets(renderTargetView);
            d3dDeviceContext.ClearRenderTargetView(renderTargetView, new SharpDX.Color(32, 166, 178));

            d3dDeviceContext.InputAssembler.SetVertexBuffers(0, new D3D11.VertexBufferBinding(vertexBuffer, Utilities.SizeOf<Vector3>(), 0));
            d3dDeviceContext.Draw(dotsArray.Count(), 0);

            swapChain.Present(1, PresentFlags.None);


            


        }           
        private void btnReset_Click(object sender, EventArgs e)
        {
            sw.Restart();
            Log("Clearing RenderTargetView.");
            d3dDeviceContext.OutputMerger.SetRenderTargets(renderTargetView);
            d3dDeviceContext.ClearRenderTargetView(renderTargetView, new SharpDX.Color(32, 103, 178));
            swapChain.Present(1, PresentFlags.None);
            Log("Reset completed. Time used: " + sw.ElapsedMilliseconds + " ms");
            sw.Stop();

        }

        private void btnRenderDots_Click(object sender, EventArgs e)
        {
            Log("Start rendering dots...");
            RenderDots();
            
        }

        private void openGLControl1_Load(object sender, EventArgs e)
        {
       
        }
    }
}
