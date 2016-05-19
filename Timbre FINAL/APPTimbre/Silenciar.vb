Public Class Silenciar
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If Dias.TextLength < 2 Then
            MsgBox("Debe tener dos cifras")
        Else
            Principal.Silencio()
        End If

    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Principal.Dessilencio()
    End Sub

    Private Sub Silencio_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub
End Class