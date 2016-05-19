<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class HoraYFecha
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
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

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(HoraYFecha))
        Me.TxtHora = New System.Windows.Forms.TextBox()
        Me.TxtMinutos = New System.Windows.Forms.TextBox()
        Me.Dias = New System.Windows.Forms.ComboBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.BtnSet = New System.Windows.Forms.Button()
        Me.AxWinsockHora = New AxMSWinsockLib.AxWinsock()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        CType(Me.AxWinsockHora, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'TxtHora
        '
        Me.TxtHora.Font = New System.Drawing.Font("Microsoft Sans Serif", 16.0!)
        Me.TxtHora.Location = New System.Drawing.Point(12, 48)
        Me.TxtHora.MaxLength = 2
        Me.TxtHora.Name = "TxtHora"
        Me.TxtHora.Size = New System.Drawing.Size(53, 32)
        Me.TxtHora.TabIndex = 2
        '
        'TxtMinutos
        '
        Me.TxtMinutos.Font = New System.Drawing.Font("Microsoft Sans Serif", 16.0!)
        Me.TxtMinutos.Location = New System.Drawing.Point(110, 48)
        Me.TxtMinutos.MaxLength = 2
        Me.TxtMinutos.Name = "TxtMinutos"
        Me.TxtMinutos.Size = New System.Drawing.Size(53, 32)
        Me.TxtMinutos.TabIndex = 3
        '
        'Dias
        '
        Me.Dias.FormattingEnabled = True
        Me.Dias.Items.AddRange(New Object() {"Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom"})
        Me.Dias.Location = New System.Drawing.Point(33, 103)
        Me.Dias.Name = "Dias"
        Me.Dias.Size = New System.Drawing.Size(121, 21)
        Me.Dias.TabIndex = 2
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(12, 31)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(33, 13)
        Me.Label1.TabIndex = 3
        Me.Label1.Text = "Hora:"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(107, 31)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(47, 13)
        Me.Label2.TabIndex = 4
        Me.Label2.Text = "Minutos:"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(30, 87)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(23, 13)
        Me.Label3.TabIndex = 5
        Me.Label3.Text = "Dia"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(28, 9)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(135, 13)
        Me.Label4.TabIndex = 6
        Me.Label4.Text = "Setear Horario y Dia Actual"
        '
        'BtnSet
        '
        Me.BtnSet.Location = New System.Drawing.Point(33, 130)
        Me.BtnSet.Name = "BtnSet"
        Me.BtnSet.Size = New System.Drawing.Size(121, 44)
        Me.BtnSet.TabIndex = 1
        Me.BtnSet.Text = "Setear"
        Me.BtnSet.UseVisualStyleBackColor = True
        '
        'AxWinsockHora
        '
        Me.AxWinsockHora.Enabled = True
        Me.AxWinsockHora.Location = New System.Drawing.Point(-48, 144)
        Me.AxWinsockHora.Name = "AxWinsockHora"
        Me.AxWinsockHora.OcxState = CType(resources.GetObject("AxWinsockHora.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxWinsockHora.Size = New System.Drawing.Size(28, 28)
        Me.AxWinsockHora.TabIndex = 7
        '
        'Timer1
        '
        '
        'HoraYFecha
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(197, 183)
        Me.Controls.Add(Me.AxWinsockHora)
        Me.Controls.Add(Me.BtnSet)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Dias)
        Me.Controls.Add(Me.TxtMinutos)
        Me.Controls.Add(Me.TxtHora)
        Me.Name = "HoraYFecha"
        Me.Text = "Hora&Fecha"
        CType(Me.AxWinsockHora, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents TxtHora As System.Windows.Forms.TextBox
    Friend WithEvents TxtMinutos As System.Windows.Forms.TextBox
    Friend WithEvents Dias As System.Windows.Forms.ComboBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents BtnSet As System.Windows.Forms.Button
    Friend WithEvents AxWinsockHora As AxMSWinsockLib.AxWinsock
    Friend WithEvents Timer1 As Timer
End Class
