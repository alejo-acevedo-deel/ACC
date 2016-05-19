<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Seteos
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()>
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
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.BtnSetear = New System.Windows.Forms.Button()
        Me.TxtMinutos = New System.Windows.Forms.TextBox()
        Me.TxtHora = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.TC = New System.Windows.Forms.RadioButton()
        Me.TL = New System.Windows.Forms.RadioButton()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(38, 9)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(76, 13)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Hora : Minutos"
        '
        'BtnSetear
        '
        Me.BtnSetear.Location = New System.Drawing.Point(39, 76)
        Me.BtnSetear.Name = "BtnSetear"
        Me.BtnSetear.Size = New System.Drawing.Size(75, 23)
        Me.BtnSetear.TabIndex = 3
        Me.BtnSetear.Text = "Setear"
        Me.BtnSetear.UseVisualStyleBackColor = True
        '
        'TxtMinutos
        '
        Me.TxtMinutos.Font = New System.Drawing.Font("Microsoft Sans Serif", 16.0!)
        Me.TxtMinutos.Location = New System.Drawing.Point(99, 38)
        Me.TxtMinutos.MaxLength = 2
        Me.TxtMinutos.Name = "TxtMinutos"
        Me.TxtMinutos.Size = New System.Drawing.Size(40, 32)
        Me.TxtMinutos.TabIndex = 2
        Me.TxtMinutos.Text = "MM"
        '
        'TxtHora
        '
        Me.TxtHora.Font = New System.Drawing.Font("Microsoft Sans Serif", 16.0!)
        Me.TxtHora.Location = New System.Drawing.Point(12, 38)
        Me.TxtHora.MaxLength = 2
        Me.TxtHora.Name = "TxtHora"
        Me.TxtHora.Size = New System.Drawing.Size(40, 32)
        Me.TxtHora.TabIndex = 1
        Me.TxtHora.Text = "HH"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(71, 50)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(10, 13)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = ":"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(9, 102)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(74, 13)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "Formato 24hs."
        '
        'TC
        '
        Me.TC.AutoSize = True
        Me.TC.Checked = True
        Me.TC.Location = New System.Drawing.Point(148, 38)
        Me.TC.Name = "TC"
        Me.TC.Size = New System.Drawing.Size(107, 17)
        Me.TC.TabIndex = 7
        Me.TC.Text = "TIMBRE CORTO"
        Me.TC.UseVisualStyleBackColor = True
        '
        'TL
        '
        Me.TL.AutoSize = True
        Me.TL.Location = New System.Drawing.Point(148, 61)
        Me.TL.Name = "TL"
        Me.TL.Size = New System.Drawing.Size(106, 17)
        Me.TL.TabIndex = 8
        Me.TL.Text = "TIMBRE LARGO"
        Me.TL.UseVisualStyleBackColor = True
        '
        'Seteos
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(266, 116)
        Me.Controls.Add(Me.TL)
        Me.Controls.Add(Me.TC)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.TxtHora)
        Me.Controls.Add(Me.TxtMinutos)
        Me.Controls.Add(Me.BtnSetear)
        Me.Controls.Add(Me.Label1)
        Me.Name = "Seteos"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Setear timbres"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents BtnSetear As System.Windows.Forms.Button
    Friend WithEvents TxtMinutos As System.Windows.Forms.TextBox
    Friend WithEvents TxtHora As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents TC As System.Windows.Forms.RadioButton
    Friend WithEvents TL As System.Windows.Forms.RadioButton
End Class
