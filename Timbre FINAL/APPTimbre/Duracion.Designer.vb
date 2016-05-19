<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Duracion
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Duracion))
        Me.Label1 = New System.Windows.Forms.Label()
        Me.TimbreLargoTxt = New System.Windows.Forms.TextBox()
        Me.TimbreCortoTxt = New System.Windows.Forms.TextBox()
        Me.ConfgiBtn = New System.Windows.Forms.Button()
        Me.AxWinsockDura = New AxMSWinsockLib.AxWinsock()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        CType(Me.AxWinsockDura, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(12, 9)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(117, 26)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Duracion En Segundos" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "(Dos Cifras)"
        '
        'TimbreLargoTxt
        '
        Me.TimbreLargoTxt.Location = New System.Drawing.Point(12, 38)
        Me.TimbreLargoTxt.Name = "TimbreLargoTxt"
        Me.TimbreLargoTxt.Size = New System.Drawing.Size(117, 20)
        Me.TimbreLargoTxt.TabIndex = 1
        Me.TimbreLargoTxt.Text = "Timbre Largo"
        '
        'TimbreCortoTxt
        '
        Me.TimbreCortoTxt.Location = New System.Drawing.Point(12, 64)
        Me.TimbreCortoTxt.Name = "TimbreCortoTxt"
        Me.TimbreCortoTxt.Size = New System.Drawing.Size(117, 20)
        Me.TimbreCortoTxt.TabIndex = 2
        Me.TimbreCortoTxt.Text = "Timbre Corto"
        '
        'ConfgiBtn
        '
        Me.ConfgiBtn.Location = New System.Drawing.Point(12, 91)
        Me.ConfgiBtn.Name = "ConfgiBtn"
        Me.ConfgiBtn.Size = New System.Drawing.Size(117, 44)
        Me.ConfgiBtn.TabIndex = 3
        Me.ConfgiBtn.Text = "Configurar"
        Me.ConfgiBtn.UseVisualStyleBackColor = True
        '
        'AxWinsockDura
        '
        Me.AxWinsockDura.Enabled = True
        Me.AxWinsockDura.Location = New System.Drawing.Point(101, 103)
        Me.AxWinsockDura.Name = "AxWinsockDura"
        Me.AxWinsockDura.OcxState = CType(resources.GetObject("AxWinsockDura.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxWinsockDura.Size = New System.Drawing.Size(28, 28)
        Me.AxWinsockDura.TabIndex = 4
        '
        'Timer1
        '
        '
        'Duracion
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(142, 143)
        Me.Controls.Add(Me.AxWinsockDura)
        Me.Controls.Add(Me.ConfgiBtn)
        Me.Controls.Add(Me.TimbreCortoTxt)
        Me.Controls.Add(Me.TimbreLargoTxt)
        Me.Controls.Add(Me.Label1)
        Me.Name = "Duracion"
        Me.Text = "Duracion"
        CType(Me.AxWinsockDura, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents Label1 As Label
    Friend WithEvents TimbreLargoTxt As TextBox
    Friend WithEvents TimbreCortoTxt As TextBox
    Friend WithEvents ConfgiBtn As Button
    Friend WithEvents AxWinsockDura As AxMSWinsockLib.AxWinsock
    Friend WithEvents Timer1 As Timer
End Class
