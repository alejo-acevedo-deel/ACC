Public Class Seteos

    Private Sub Button1_Click(ByVal sender As Object, ByVal e As EventArgs) Handles BtnSetear.Click

        If TxtHora.Text < 0 Or TxtHora.Text > 24 Then
            MessageBox.Show("Hora debe estar entre 00 y 24")
        ElseIf TxtMinutos.Text < 0 Or TxtMinutos.Text > 59 Then
            MessageBox.Show("Minutos debe estar entre 00 y 59")

        ElseIf TxtHora.Text.Length < 2 Then
            MessageBox.Show("formato incorrecto hora ")
        ElseIf TxtMinutos.Text.Length < 2 Then
            MessageBox.Show("formato incorrecto minutos")
        Else

            If TC.Checked = True Then
                Module1.Duracion = 0
                Hora = TxtHora.Text & (" ") & (":") & (" ") & TxtMinutos.Text & ("    TIMBRE CORTO")
                Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
            Else
                Module1.Duracion = 1
                Hora = TxtHora.Text & (" ") & (":") & (" ") & TxtMinutos.Text & ("    TIMBRE LARGO")
                Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
            End If
        End If

    End Sub

    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Sub RadioButton1_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TC.CheckedChanged

    End Sub

    Private Sub TxtHora_KeyPress(sender As Object, e As KeyPressEventArgs) Handles TxtHora.KeyPress
        If Char.IsNumber(e.KeyChar) Then
            e.Handled = False
        ElseIf Char.IsControl(e.KeyChar) Then
            e.Handled = False
        Else
            e.Handled = True
        End If
    End Sub

    Private Sub TxtMinutos_KeyPress(sender As Object, e As KeyPressEventArgs) Handles TxtMinutos.KeyPress
        If Char.IsNumber(e.KeyChar) Then
            e.Handled = False
        ElseIf Char.IsControl(e.KeyChar) Then
            e.Handled = False
        Else
            e.Handled = True
        End If
    End Sub

    Private Sub Button1_Click_1(sender As Object, e As EventArgs)
        Hora = ("07") & (" ") & (":") & (" ") & ("30") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("08") & (" ") & (":") & (" ") & ("10") & ("    TIMBRE CORTO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("08") & (" ") & (":") & (" ") & ("50") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("09") & (" ") & (":") & (" ") & ("05") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("09") & (" ") & (":") & (" ") & ("45") & ("    TIMBRE CORTO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("10") & (" ") & (":") & (" ") & ("25") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("10") & (" ") & (":") & (" ") & ("40") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("11") & (" ") & (":") & (" ") & ("20") & ("    TIMBRE CORTO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("12") & (" ") & (":") & (" ") & ("00") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("12") & (" ") & (":") & (" ") & ("40") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)


    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs)
        Hora = ("13") & (" ") & (":") & (" ") & ("30") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("14") & (" ") & (":") & (" ") & ("10") & ("    TIMBRE CORTO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("14") & (" ") & (":") & (" ") & ("50") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("15") & (" ") & (":") & (" ") & ("05") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("15") & (" ") & (":") & (" ") & ("45") & ("    TIMBRE CORTO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("16") & (" ") & (":") & (" ") & ("25") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("16") & (" ") & (":") & (" ") & ("40") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("17") & (" ") & (":") & (" ") & ("20") & ("    TIMBRE CORTO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("18") & (" ") & (":") & (" ") & ("00") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
        Hora = ("18") & (" ") & (":") & (" ") & ("40") & ("    TIMBRE LARGO")
        Principal.ASetear.Items.Add(item:=Hora, isChecked:=True)
    End Sub
End Class