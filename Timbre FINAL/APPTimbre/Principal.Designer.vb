

<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Principal
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

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()>
    Public Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Principal))
        Me.BtnAct = New System.Windows.Forms.Button()
        Me.Timbres2 = New System.Windows.Forms.ComboBox()
        Me.Timbres1 = New System.Windows.Forms.ComboBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.Progress = New System.Windows.Forms.ProgressBar()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Agregar = New System.Windows.Forms.Button()
        Me.ASetear = New System.Windows.Forms.CheckedListBox()
        Me.Seteados = New System.Windows.Forms.CheckedListBox()
        Me.Borrar = New System.Windows.Forms.Button()
        Me.Quitar = New System.Windows.Forms.Button()
        Me.ToolStrip1 = New System.Windows.Forms.ToolStrip()
        Me.Configuraciones = New System.Windows.Forms.ToolStripDropDownButton()
        Me.FechaHora = New System.Windows.Forms.ToolStripMenuItem()
        Me.Vacaciones = New System.Windows.Forms.ToolStripMenuItem()
        Me.DuracionToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LibresToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.Sistema = New System.Windows.Forms.ToolStripDropDownButton()
        Me.Estado = New System.Windows.Forms.ToolStripMenuItem()
        Me.Ayuda = New System.Windows.Forms.ToolStripDropDownButton()
        Me.AcercaDeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.UsuarioToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AgregarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ModificarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BorrarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.TimbresToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BorrarTodo = New System.Windows.Forms.Button()
        Me.Exportar = New System.Windows.Forms.Button()
        Me.Silenc = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.AxWinsock1 = New AxMSWinsockLib.AxWinsock()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Timer2 = New System.Windows.Forms.Timer(Me.components)
        Me.ToolStrip1.SuspendLayout()
        CType(Me.AxWinsock1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'BtnAct
        '
        Me.BtnAct.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.BtnAct.Location = New System.Drawing.Point(626, 305)
        Me.BtnAct.Name = "BtnAct"
        Me.BtnAct.Size = New System.Drawing.Size(75, 22)
        Me.BtnAct.TabIndex = 22
        Me.BtnAct.TabStop = False
        Me.BtnAct.Text = "Actualizar"
        Me.BtnAct.UseVisualStyleBackColor = True
        '
        'Timbres2
        '
        Me.Timbres2.FormattingEnabled = True
        Me.Timbres2.Items.AddRange(New Object() {"Timbre"})
        Me.Timbres2.Location = New System.Drawing.Point(426, 57)
        Me.Timbres2.Name = "Timbres2"
        Me.Timbres2.Size = New System.Drawing.Size(275, 21)
        Me.Timbres2.TabIndex = 24
        Me.Timbres2.TabStop = False
        '
        'Timbres1
        '
        Me.Timbres1.AllowDrop = True
        Me.Timbres1.FormattingEnabled = True
        Me.Timbres1.Items.AddRange(New Object() {"Timbre"})
        Me.Timbres1.Location = New System.Drawing.Point(12, 57)
        Me.Timbres1.Name = "Timbres1"
        Me.Timbres1.Size = New System.Drawing.Size(275, 21)
        Me.Timbres1.TabIndex = 28
        Me.Timbres1.TabStop = False
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Label2.Location = New System.Drawing.Point(522, 25)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(120, 13)
        Me.Label2.TabIndex = 30
        Me.Label2.Text = "Estado actual del timbre"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Label3.Location = New System.Drawing.Point(423, 41)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(39, 13)
        Me.Label3.TabIndex = 31
        Me.Label3.Text = "Timbre"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Label5.Location = New System.Drawing.Point(12, 41)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(39, 13)
        Me.Label5.TabIndex = 33
        Me.Label5.Text = "Timbre"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Label6.Location = New System.Drawing.Point(54, 25)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(177, 13)
        Me.Label6.TabIndex = 35
        Me.Label6.Text = "Agregar configuracion para el timbre"
        '
        'Progress
        '
        Me.Progress.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Progress.Location = New System.Drawing.Point(556, 344)
        Me.Progress.Name = "Progress"
        Me.Progress.Size = New System.Drawing.Size(145, 23)
        Me.Progress.TabIndex = 39
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!)
        Me.Label7.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Label7.Location = New System.Drawing.Point(477, 344)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(73, 20)
        Me.Label7.TabIndex = 40
        Me.Label7.Text = "Progreso"
        '
        'Agregar
        '
        Me.Agregar.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Agregar.Location = New System.Drawing.Point(121, 302)
        Me.Agregar.Name = "Agregar"
        Me.Agregar.Size = New System.Drawing.Size(75, 23)
        Me.Agregar.TabIndex = 41
        Me.Agregar.TabStop = False
        Me.Agregar.Text = "Agregar"
        Me.Agregar.UseVisualStyleBackColor = True
        '
        'ASetear
        '
        Me.ASetear.CheckOnClick = True
        Me.ASetear.FormattingEnabled = True
        Me.ASetear.Location = New System.Drawing.Point(12, 82)
        Me.ASetear.Name = "ASetear"
        Me.ASetear.Size = New System.Drawing.Size(275, 214)
        Me.ASetear.Sorted = True
        Me.ASetear.TabIndex = 42
        Me.ASetear.TabStop = False
        '
        'Seteados
        '
        Me.Seteados.AccessibleDescription = ""
        Me.Seteados.CheckOnClick = True
        Me.Seteados.FormattingEnabled = True
        Me.Seteados.Location = New System.Drawing.Point(426, 84)
        Me.Seteados.Name = "Seteados"
        Me.Seteados.Size = New System.Drawing.Size(275, 214)
        Me.Seteados.TabIndex = 43
        Me.Seteados.TabStop = False
        '
        'Borrar
        '
        Me.Borrar.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Borrar.Location = New System.Drawing.Point(12, 302)
        Me.Borrar.Name = "Borrar"
        Me.Borrar.Size = New System.Drawing.Size(91, 35)
        Me.Borrar.TabIndex = 44
        Me.Borrar.TabStop = False
        Me.Borrar.Text = "Borrar" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "Seleccionados"
        Me.Borrar.UseVisualStyleBackColor = True
        '
        'Quitar
        '
        Me.Quitar.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Quitar.Location = New System.Drawing.Point(525, 304)
        Me.Quitar.Name = "Quitar"
        Me.Quitar.Size = New System.Drawing.Size(75, 23)
        Me.Quitar.TabIndex = 45
        Me.Quitar.TabStop = False
        Me.Quitar.Text = "Quitar"
        Me.Quitar.UseVisualStyleBackColor = True
        '
        'ToolStrip1
        '
        Me.ToolStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.Configuraciones, Me.Sistema, Me.Ayuda})
        Me.ToolStrip1.Location = New System.Drawing.Point(0, 0)
        Me.ToolStrip1.Name = "ToolStrip1"
        Me.ToolStrip1.Size = New System.Drawing.Size(714, 25)
        Me.ToolStrip1.TabIndex = 46
        Me.ToolStrip1.Text = "ToolStrip1"
        '
        'Configuraciones
        '
        Me.Configuraciones.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
        Me.Configuraciones.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FechaHora, Me.Vacaciones, Me.DuracionToolStripMenuItem, Me.LibresToolStripMenuItem})
        Me.Configuraciones.Image = CType(resources.GetObject("Configuraciones.Image"), System.Drawing.Image)
        Me.Configuraciones.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.Configuraciones.Name = "Configuraciones"
        Me.Configuraciones.Size = New System.Drawing.Size(96, 22)
        Me.Configuraciones.Text = "Configuracion"
        '
        'FechaHora
        '
        Me.FechaHora.Name = "FechaHora"
        Me.FechaHora.Size = New System.Drawing.Size(143, 22)
        Me.FechaHora.Text = "Fecha y Hora"
        '
        'Vacaciones
        '
        Me.Vacaciones.Name = "Vacaciones"
        Me.Vacaciones.Size = New System.Drawing.Size(143, 22)
        Me.Vacaciones.Text = "Vacaciones"
        '
        'DuracionToolStripMenuItem
        '
        Me.DuracionToolStripMenuItem.Name = "DuracionToolStripMenuItem"
        Me.DuracionToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.DuracionToolStripMenuItem.Text = "Duracion"
        '
        'LibresToolStripMenuItem
        '
        Me.LibresToolStripMenuItem.Name = "LibresToolStripMenuItem"
        Me.LibresToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.LibresToolStripMenuItem.Text = "Libres"
        '
        'Sistema
        '
        Me.Sistema.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
        Me.Sistema.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.Estado})
        Me.Sistema.Image = CType(resources.GetObject("Sistema.Image"), System.Drawing.Image)
        Me.Sistema.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.Sistema.Name = "Sistema"
        Me.Sistema.Size = New System.Drawing.Size(61, 22)
        Me.Sistema.Text = "Sistema"
        '
        'Estado
        '
        Me.Estado.Name = "Estado"
        Me.Estado.Size = New System.Drawing.Size(109, 22)
        Me.Estado.Text = "Estado"
        '
        'Ayuda
        '
        Me.Ayuda.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.Ayuda.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.AcercaDeToolStripMenuItem, Me.UsuarioToolStripMenuItem, Me.TimbresToolStripMenuItem})
        Me.Ayuda.Image = CType(resources.GetObject("Ayuda.Image"), System.Drawing.Image)
        Me.Ayuda.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.Ayuda.Name = "Ayuda"
        Me.Ayuda.Size = New System.Drawing.Size(29, 22)
        Me.Ayuda.Text = "Ayuda"
        '
        'AcercaDeToolStripMenuItem
        '
        Me.AcercaDeToolStripMenuItem.Name = "AcercaDeToolStripMenuItem"
        Me.AcercaDeToolStripMenuItem.Size = New System.Drawing.Size(151, 22)
        Me.AcercaDeToolStripMenuItem.Text = "Acerca de..."
        '
        'UsuarioToolStripMenuItem
        '
        Me.UsuarioToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.AgregarToolStripMenuItem, Me.ModificarToolStripMenuItem, Me.BorrarToolStripMenuItem})
        Me.UsuarioToolStripMenuItem.Name = "UsuarioToolStripMenuItem"
        Me.UsuarioToolStripMenuItem.Size = New System.Drawing.Size(151, 22)
        Me.UsuarioToolStripMenuItem.Text = "Usuario"
        '
        'AgregarToolStripMenuItem
        '
        Me.AgregarToolStripMenuItem.Name = "AgregarToolStripMenuItem"
        Me.AgregarToolStripMenuItem.Size = New System.Drawing.Size(125, 22)
        Me.AgregarToolStripMenuItem.Text = "Agregar"
        '
        'ModificarToolStripMenuItem
        '
        Me.ModificarToolStripMenuItem.Name = "ModificarToolStripMenuItem"
        Me.ModificarToolStripMenuItem.Size = New System.Drawing.Size(125, 22)
        Me.ModificarToolStripMenuItem.Text = "Modificar"
        '
        'BorrarToolStripMenuItem
        '
        Me.BorrarToolStripMenuItem.Name = "BorrarToolStripMenuItem"
        Me.BorrarToolStripMenuItem.Size = New System.Drawing.Size(125, 22)
        Me.BorrarToolStripMenuItem.Text = "Borrar"
        '
        'TimbresToolStripMenuItem
        '
        Me.TimbresToolStripMenuItem.Name = "TimbresToolStripMenuItem"
        Me.TimbresToolStripMenuItem.Size = New System.Drawing.Size(151, 22)
        Me.TimbresToolStripMenuItem.Text = "Admin Timbre"
        '
        'BorrarTodo
        '
        Me.BorrarTodo.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.BorrarTodo.Location = New System.Drawing.Point(212, 302)
        Me.BorrarTodo.Name = "BorrarTodo"
        Me.BorrarTodo.Size = New System.Drawing.Size(75, 23)
        Me.BorrarTodo.TabIndex = 47
        Me.BorrarTodo.TabStop = False
        Me.BorrarTodo.Text = "Borrar Todo"
        Me.BorrarTodo.UseVisualStyleBackColor = True
        '
        'Exportar
        '
        Me.Exportar.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.Exportar.Location = New System.Drawing.Point(293, 143)
        Me.Exportar.Name = "Exportar"
        Me.Exportar.Size = New System.Drawing.Size(127, 62)
        Me.Exportar.TabIndex = 1
        Me.Exportar.Text = "Exportar cambios >"
        Me.Exportar.UseVisualStyleBackColor = True
        '
        'Silenc
        '
        Me.Silenc.Location = New System.Drawing.Point(426, 304)
        Me.Silenc.Name = "Silenc"
        Me.Silenc.Size = New System.Drawing.Size(75, 23)
        Me.Silenc.TabIndex = 48
        Me.Silenc.TabStop = False
        Me.Silenc.Text = "Silenciar"
        Me.Silenc.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, CType((System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.FontStyle), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(12, 356)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(45, 20)
        Me.Label1.TabIndex = 49
        Me.Label1.Text = "ACC"
        '
        'AxWinsock1
        '
        Me.AxWinsock1.Enabled = True
        Me.AxWinsock1.Location = New System.Drawing.Point(194, 0)
        Me.AxWinsock1.Name = "AxWinsock1"
        Me.AxWinsock1.OcxState = CType(resources.GetObject("AxWinsock1.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxWinsock1.Size = New System.Drawing.Size(28, 28)
        Me.AxWinsock1.TabIndex = 50
        '
        'Timer1
        '
        '
        'Timer2
        '
        Me.Timer2.Interval = 600
        '
        'Principal
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(714, 380)
        Me.Controls.Add(Me.AxWinsock1)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Silenc)
        Me.Controls.Add(Me.BorrarTodo)
        Me.Controls.Add(Me.ToolStrip1)
        Me.Controls.Add(Me.Quitar)
        Me.Controls.Add(Me.Borrar)
        Me.Controls.Add(Me.Seteados)
        Me.Controls.Add(Me.ASetear)
        Me.Controls.Add(Me.Agregar)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.Progress)
        Me.Controls.Add(Me.Exportar)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Timbres1)
        Me.Controls.Add(Me.Timbres2)
        Me.Controls.Add(Me.BtnAct)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximumSize = New System.Drawing.Size(730, 419)
        Me.Name = "Principal"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Timbre "
        Me.ToolStrip1.ResumeLayout(False)
        Me.ToolStrip1.PerformLayout()
        CType(Me.AxWinsock1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents BtnAct As System.Windows.Forms.Button
    Friend WithEvents Timbres2 As System.Windows.Forms.ComboBox
    Friend WithEvents Timbres1 As System.Windows.Forms.ComboBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents Progress As System.Windows.Forms.ProgressBar
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents Agregar As System.Windows.Forms.Button
    Friend WithEvents ASetear As System.Windows.Forms.CheckedListBox
    Public WithEvents Seteados As System.Windows.Forms.CheckedListBox
    Friend WithEvents Borrar As System.Windows.Forms.Button
    Friend WithEvents Quitar As System.Windows.Forms.Button
    Friend WithEvents ToolStrip1 As System.Windows.Forms.ToolStrip
    Friend WithEvents Configuraciones As System.Windows.Forms.ToolStripDropDownButton
    Friend WithEvents FechaHora As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents Sistema As System.Windows.Forms.ToolStripDropDownButton
    Friend WithEvents Estado As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BorrarTodo As System.Windows.Forms.Button
    Friend WithEvents Vacaciones As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents Exportar As System.Windows.Forms.Button
    Friend WithEvents Silenc As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Ayuda As System.Windows.Forms.ToolStripDropDownButton
    Friend WithEvents AcercaDeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents UsuarioToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents AgregarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ModificarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents DuracionToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents BorrarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents LibresToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents TimbresToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SerialPort1 As IO.Ports.SerialPort
    Private components As System.ComponentModel.IContainer
    Friend WithEvents AxWinsock1 As AxMSWinsockLib.AxWinsock
    Friend WithEvents Timer1 As Timer
    Friend WithEvents Timer2 As Timer
End Class
