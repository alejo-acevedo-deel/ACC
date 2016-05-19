Imports System.Text

Public Class Duracion
    Dim IP As Integer
    Dim Acc As Integer
    Dim a As Integer
    Dim B As Integer = 1
    Dim datos(50) As String
    Private Sub ConfgiBtn_Click(sender As Object, e As EventArgs) Handles ConfgiBtn.Click
        IP = 1
        Acc = 2
        If TimbreCortoTxt.TextLength < 2 Then
            MsgBox("Ingrese dos digitos")
        ElseIf TimbreLargoTxt.TextLength < 2
            MsgBox("Ingrese dos digitos")
        Else
            AxWinsockDura.Close()
            AxWinsockDura.RemoteHost = My.Settings.IP.Item(IP)
            Try
                With AxWinsockDura
                    .RemotePort = ("35")
                    'Me conecto
                    .Connect()
                End With
            Catch ex As Net.Sockets.SocketException
                MsgBox("El Timbre No Se Ha Podido Configurar", MsgBoxStyle.Critical)
            End Try
        End If
    End Sub

    Private Sub EnvioDuracion()
        AxWinsockDura.SendData(Encoding.ASCII.GetBytes(("Dura   ") & TimbreLargoTxt.Text() & (" ") & TimbreCortoTxt.Text & (";")))

    End Sub

    Private Sub Duracion_FormClosing(sender As Object, e As FormClosingEventArgs) Handles MyBase.FormClosing
        AxWinsockDura.Close()
    End Sub

    Private Sub AxWinsockDura_ConnectEvent(sender As Object, e As EventArgs) Handles AxWinsockDura.ConnectEvent
        If Acc = 1 Then
            Timer1.Stop()
            AxWinsockDura.SendData(Encoding.ASCII.GetBytes("Durar "))
        End If
        If Acc = 2 Then
            Timer1.Stop()
            EnvioDuracion()
        End If
    End Sub

    Private Sub Duracion_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Tipo = 4
        Acc = 1
        a = 1
        AxWinsockDura.RemoteHost = My.Settings.IP.Item(a)
        ''Determino a donde se quiere conectar el usuario
        AxWinsockDura.RemotePort = ("35")
        AxWinsockDura.Connect()
        Timer1.Start()
    End Sub

    Private Sub AxWinsockDura_DataArrival(sender As Object, e As AxMSWinsockLib.DMSWinsockControlEvents_DataArrivalEvent) Handles AxWinsockDura.DataArrival
        Dim dato As Object
        Dim OK As Boolean
        AxWinsockDura.GetData(dato)
        datos(B) = Encoding.ASCII.GetString(dato)
        B = B + 1
        AxWinsockDura.Close()
        If a < My.Settings.IP.Count - 1 Then
            a = a + 1
            AxWinsockDura.RemoteHost = My.Settings.IP.Item(a)
            AxWinsockDura.Connect()
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
    Public Sub Respuesta()
        TimbreLargoTxt.Text = datos(1).Remove(datos(1).IndexOf("C"), 4)
        TimbreCortoTxt.Text = datos(1).Remove(datos(1).IndexOf("L"), 3).Remove(datos(1).IndexOf("C"), 1)
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Dim OK As Boolean
        Timer1.Stop()
        MsgBox("Algun dispositivo no pudo ser conectado")
        If Acc = 1 Then
            AxWinsockDura.Close()
            If a < My.Settings.IP.Count - 1 Then
                a = a + 1
                AxWinsockDura.RemoteHost = My.Settings.IP.Item(a)
                AxWinsockDura.Connect()
                Timer1.Start()
            Else
                For h As Integer = 1 To B
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
            If IP < My.Settings.IP.Count - 1 Then
                IP = IP + 1
                AxWinsockDura.Close()
                AxWinsockDura.RemoteHost = My.Settings.IP.Item(IP)
                AxWinsockDura.Connect()
                Timer1.Start()
            End If
        End If
    End Sub

    Private Sub AxWinsockDura_SendComplete(sender As Object, e As EventArgs) Handles AxWinsockDura.SendComplete
        If Acc = 2 Then
            AxWinsockDura.Close()
            If IP < My.Settings.IP.Count - 1 Then
                IP = IP + 1
                AxWinsockDura.RemoteHost = My.Settings.IP.Item(IP)
                Try
                    With AxWinsockDura
                        .RemotePort = 35
                        'Me conecto
                        .Connect()
                    End With
                    Timer1.Start()
                Catch ex As Exception
                    MsgBox("El " & My.Settings.Timbre(IP) & " No Se Ha Podido Poner En Modo Vacaciones", MsgBoxStyle.Critical)
                End Try
            End If
        End If

    End Sub
End Class