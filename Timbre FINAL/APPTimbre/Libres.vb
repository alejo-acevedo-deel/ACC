Imports System.Text
Public Class Libres
    Dim Send As String
    Dim Acc As Integer
    Dim Timbre As Integer
    Dim a As Integer
    Dim datos(50) As String
    Dim B As Integer
    Private Sub ComboBox3_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox3.SelectedIndexChanged
        If ((ComboBox3.SelectedItem() = "Suena")) Then
            Try
                Send = Send.Replace(" Lun", "")
            Catch ex As Exception

            End Try
        End If
        If ((ComboBox3.SelectedItem() = "No Suena")) Then
            If (Send.Contains(" Lun") = False) Then
                Send = (Send & (" Lun"))
            End If
        End If
    End Sub

    Private Sub ComboBox2_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox2.SelectedIndexChanged
        If ((ComboBox2.SelectedItem() = "Suena")) Then
            Try
                Send = Send.Replace(" Mar", "")
            Catch ex As Exception

            End Try
        End If
        If ((ComboBox2.SelectedItem() = "No Suena")) Then
            If (Send.Contains(" Mar") = False) Then
                Send = (Send & (" Mar"))
            End If
        End If
    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedIndexChanged
        If ((ComboBox1.SelectedItem() = "Suena")) Then
            Try
                Send = Send.Replace(" Mie", "")
            Catch ex As Exception

            End Try
        End If
        If ((ComboBox1.SelectedItem() = "No Suena")) Then
            If (Send.Contains(" Mie") = False) Then
                Send = (Send & (" Mie"))
            End If
        End If
    End Sub

    Private Sub ComboBox4_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox4.SelectedIndexChanged
        If ((ComboBox4.SelectedItem() = "Suena")) Then
            Try
                Send = Send.Replace(" Jue", "")
            Catch ex As Exception

            End Try
        End If
        If ((ComboBox4.SelectedItem() = "No Suena")) Then
            If (Send.Contains(" Jue") = False) Then
                Send = (Send & (" Jue"))
            End If
        End If
    End Sub

    Private Sub ComboBox5_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox5.SelectedIndexChanged
        If ((ComboBox5.SelectedItem() = "Suena")) Then
            Try
                Send = Send.Replace(" Vie", "")
            Catch ex As Exception

            End Try
        End If
        If ((ComboBox5.SelectedItem() = "No Suena")) Then
            If (Send.Contains(" Vie") = False) Then
                Send = (Send & (" Vie"))
            End If
        End If
    End Sub

    Private Sub ComboBox6_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox6.SelectedIndexChanged
        If ((ComboBox6.SelectedItem() = "Suena")) Then
            Try
                Send = Send.Replace(" Sab", "")
            Catch ex As Exception

            End Try
        End If
        If ((ComboBox6.SelectedItem() = "No Suena")) Then
            If (Send.Contains(" Sab") = False) Then
                Send = (Send & (" Sab"))
            End If
        End If
    End Sub

    Private Sub ComboBox7_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox7.SelectedIndexChanged
        If ((ComboBox7.SelectedItem() = "Suena")) Then
            Try
                Send = Send.Replace(" Dom", "")
            Catch ex As Exception

            End Try
        End If
        If ((ComboBox7.SelectedItem() = "No Suena")) Then
            If (Send.Contains(" Dom") = False) Then
                Send = (Send & (" Dom"))
            End If
        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Timbre = 1
        Acc = 2
            AxWinsockLibre.Close()
            AxWinsockLibre.RemoteHost = My.Settings.IP.Item(Timbre)
            AxWinsockLibre.RemotePort = 35
        AxWinsockLibre.Connect()
        Timer1.Start()
    End Sub

    Private Sub Libres_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Send = ("Libres")
        Tipo = 3
        Acc = 1
        a = 1
        AxWinsockLibre.RemoteHost = My.Settings.IP.Item(a)
        ''Determino a donde se quiere conectar el usuario
        AxWinsockLibre.RemotePort = ("35")
        AxWinsockLibre.Connect()
        Timer1.Start()
    End Sub

    Private Sub Libres_FormClosing(sender As Object, e As FormClosingEventArgs) Handles MyBase.FormClosing
        AxWinsockLibre.Close()
    End Sub

    Private Sub AxWinsockLibre_ConnectEvent(sender As Object, e As EventArgs) Handles AxWinsockLibre.ConnectEvent
        If Acc = 1 Then
            Timer1.Stop()
            AxWinsockLibre.SendData(Encoding.ASCII.GetBytes("Libre ;"))
        End If
        If Acc = 2 Then
            Timer1.Stop()
            AxWinsockLibre.SendData(Encoding.ASCII.GetBytes(Send))
        End If
    End Sub

    Private Sub AxWinsockLibre_DataArrival(sender As Object, e As AxMSWinsockLib.DMSWinsockControlEvents_DataArrivalEvent) Handles AxWinsockLibre.DataArrival
        Dim dato As Object
        Dim OK As Boolean
        AxWinsockLibre.GetData(dato)
        datos(B) = Encoding.ASCII.GetString(dato)
        AxWinsockLibre.Close()
        B = B + 1
        If a < My.Settings.IP.Count - 1 Then
            a = a + 1
            AxWinsockLibre.RemoteHost = My.Settings.IP.Item(a)
            AxWinsockLibre.Connect()
            Timer1.Start()
        Else
            For h As Integer = 1 To B - 1
                If datos(1) = datos(h) Then
                    OK = True
                Else
                    OK = False
                    GoTo Salto
                End If
            Next
Salto:      If OK = True Then
                Respuesta()
            Else
                MsgBox("Algun dispositivo no se encuentra configurado igual a los demas, haga click en el boton configurar")
            End If
        End If
    End Sub

    Private Sub AxWinsockLibre_SendComplete(sender As Object, e As EventArgs) Handles AxWinsockLibre.SendComplete
        If Acc = 2 Then
            Libres()
        End If
    End Sub

    Private Sub Libres()
        AxWinsockLibre.Close()
        If Timbre < My.Settings.IP.Count - 1 Then
            Timbre = Timbre + 1
            AxWinsockLibre.RemoteHost = My.Settings.IP.Item(Timbre)
            AxWinsockLibre.Connect()
            Timer1.Start()
        End If
    End Sub

    Public Sub Respuesta()
        If Tipo = 3 Then
            If (datos(1).Contains("Lu")) Then
                ComboBox3.SelectedIndex = 1
            Else
                ComboBox3.SelectedIndex = 0
            End If
            If (datos(1).Contains("Ma")) Then
                ComboBox2.SelectedIndex = 1
            Else
                ComboBox2.SelectedIndex = 0
            End If
            If (datos(1).Contains("Mi")) Then
                ComboBox1.SelectedIndex = 1
            Else
                ComboBox1.SelectedIndex = 0
            End If
            If (datos(1).Contains("Ju")) Then
                ComboBox4.SelectedIndex = 1
            Else
                ComboBox4.SelectedIndex = 0
            End If
            If (datos(1).Contains("Vi")) Then
                ComboBox5.SelectedIndex = 1
            Else
                ComboBox5.SelectedIndex = 0
            End If
            If (datos(1).Contains("Sa")) Then
                ComboBox6.SelectedIndex = 1
            Else
                ComboBox6.SelectedIndex = 0
            End If
            If (datos(1).Contains("Do")) Then
                ComboBox7.SelectedIndex = 1
            Else
                ComboBox7.SelectedIndex = 0
            End If
        End If
    End Sub
    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Dim OK As Boolean
        Timer1.Stop()
        MsgBox("Algun dispositivo no pudo ser conectado")
        If Acc = 1 Then
            AxWinsockLibre.Close()
            If a < My.Settings.IP.Count - 1 Then
                a = a + 1
                AxWinsockLibre.RemoteHost = My.Settings.IP.Item(a)
                AxWinsockLibre.Connect()
                Timer1.Start()
            Else
                For h As Integer = 1 To B - 1
                    If datos(1) = datos(h) Then
                        OK = True
                    Else
                        OK = False
                    End If
                Next
                If OK = True Then
                    Respuesta()
                Else
                    MsgBox("Algun dispositivo no se encuentra configurado igual a los demas, haga click en el boton configurar")
                End If
            End If
        End If
        If Acc = 2 Then
            Libres()
        End If
    End Sub
End Class