Imports System.Text

Public Class HoraYFecha
    Dim A As Integer
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles BtnSet.Click
        AxWinsockHora.Close()
        A = 1
        If TxtHora.Text < 0 Or TxtHora.Text > 24 Then
            MessageBox.Show("Hora debe estar entre 0 y 24")
        ElseIf TxtMinutos.Text < 0 Or TxtMinutos.Text > 59 Then
            MessageBox.Show("Minutos debe estar entre 0 y 59")

        ElseIf TxtHora.Text.Length < 2 Then
            MessageBox.Show("formato incorrecto hora ")
        ElseIf TxtMinutos.Text.Length < 2 Then
            MessageBox.Show("formato incorrecto minutos")
        Else
            AxWinsockHora.RemoteHost = My.Settings.IP.Item(A)
            With AxWinsockHora
                .RemotePort = 35
                'Me conecto
                .Connect()
            End With
            Timer1.Start()
        End If
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

    Private Sub HoraYFecha_FormClosing(sender As Object, e As FormClosingEventArgs) Handles MyBase.FormClosing
        AxWinsockHora.Close()
    End Sub

    Private Sub AxWinsockHora_ConnectEvent(sender As Object, e As EventArgs) Handles AxWinsockHora.ConnectEvent
        Timer1.Stop()

        Try
            AxWinsockHora.SendData(Encoding.ASCII.GetBytes(("Hora  ") & Dias.SelectedItem() & TxtHora.Text & TxtMinutos.Text & (";")))
        Catch ex As Exception

        End Try
    End Sub

    Private Sub AxWinsockHora_SendComplete(sender As Object, e As EventArgs) Handles AxWinsockHora.SendComplete
        AxWinsockHora.Close()
        Hora()

    End Sub

    Public Sub Hora()
        A = A + 1
        If A < My.Settings.IP.Count Then
            AxWinsockHora.RemoteHost = My.Settings.IP.Item(A)
            With AxWinsockHora
                'Me conecto
                .Connect()
            End With
            Timer1.Start()
        End If
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Timer1.Stop()
        MsgBox("No se ha podido conectar al dispositivo " & My.Settings.Timbre.Item(A), MsgBoxStyle.Critical)
        AxWinsockHora.Close()
        Hora()
    End Sub
End Class