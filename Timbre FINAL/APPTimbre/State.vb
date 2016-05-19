
Imports System.Text
Imports System.Threading

Public Class EstadoForm
    Inherits System.Windows.Forms.Form
    Dim Num As Integer
    Dim Frase As String
    Dim i As Integer
    Dim TimbreTB(50) As TextBox
    Dim IPTB(50) As TextBox
    Dim HoraTB(50) As TextBox
    Dim VacaTB(50) As TextBox
    Dim b As Integer
    Dim a As Integer
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Tipo = 2
        a = 1
        AxWinsockState.Close()
        AxWinsockState.RemoteHost = My.Settings.IP.Item(a)
        'Determino a donde se quiere conectar el usuario
        AxWinsockState.RemotePort = 35
        AxWinsockState.Connect()
        Timer1.Start()
    End Sub

    Private Sub EstadoForm_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        b = 35
        For i = 1 To My.Settings.Timbre.Count - 1
            TimbreTB(i) = New TextBox
            TimbreTB(i).Location = New Point(11, b)
            TimbreTB(i).Size = New Size(117, 20)
            TimbreTB(i).ReadOnly = 1
            Controls.Add(TimbreTB(i))
            TimbreTB(i).Visible = True
            TimbreTB(i).Text = My.Settings.Timbre.Item(i)
            IPTB(i) = New TextBox
            IPTB(i).Location = New Point(157, b)
            IPTB(i).Size = New Size(117, 20)
            IPTB(i).ReadOnly = 1
            Controls.Add(IPTB(i))
            IPTB(i).Visible = True
            IPTB(i).Text = My.Settings.IP.Item(i)
            HoraTB(i) = New TextBox
            HoraTB(i).Location = New Point(300, b)
            HoraTB(i).Size = New Size(80, 20)
            HoraTB(i).ReadOnly = 1
            Controls.Add(HoraTB(i))
            HoraTB(i).Visible = True
            VacaTB(i) = New TextBox
            VacaTB(i).Location = New Point(400, b)
            VacaTB(i).Size = New Size(103, 20)
            VacaTB(i).ReadOnly = 1
            Controls.Add(VacaTB(i))
            VacaTB(i).Visible = True
            b = b + 26
        Next
        i = i - 1
        Me.AutoSizeMode = AutoSizeMode.GrowOnly
        Me.AutoSize = AutoSizeMode
        b = Me.Height
        b = b + 10
        Me.Size = New Size(Me.Width, b)
        Try
            Button1.Location = New Point(519, VacaTB(i).Location.Y)
        Catch
        End Try

    End Sub

    Private Sub EstadoForm_FormClosing(sender As Object, e As FormClosingEventArgs) Handles MyBase.FormClosing
        AxWinsockState.Close()
    End Sub

    Private Sub AxWinsockState_ConnectEvent(sender As Object, e As EventArgs) Handles AxWinsockState.ConnectEvent
        Timer1.Stop()
        TimbreTB(a).BackColor = Color.Lime
        IPTB(a).BackColor = Color.Lime
        AxWinsockState.SendData(Encoding.ASCII.GetBytes("State ;"))
    End Sub

    Private Sub AxWinsockState_DataArrival(sender As Object, e As AxMSWinsockLib.DMSWinsockControlEvents_DataArrivalEvent) Handles AxWinsockState.DataArrival
        Dim dato As Object
        Dim datos As String
        AxWinsockState.GetData(dato)
        datos = Encoding.ASCII.GetString(dato)
        If (Tipo = 2) Then
            CheckForIllegalCrossThreadCalls = False
            If (datos.Contains("On") = True) Then
                datos = datos.Replace("On", " ")
                HoraTB(a).Text = datos
                VacaTB(a).Text = "Encendido"
            End If
            If (datos.Contains("Off") = True) Then
                datos = datos.Replace("Off", " ")
                HoraTB(a).Text = datos
                VacaTB(a).Text = "Apagado"
            End If
        End If
        AxWinsockState.Close()
        State()
    End Sub

    Public Sub State()
        a = a + 1
        If a < My.Settings.IP.Count Then
            AxWinsockState.RemoteHost = My.Settings.IP.Item(a)
            'Determino a donde se quiere conectar el usuario
            AxWinsockState.RemotePort = 35
            AxWinsockState.Connect()
            Timer1.Start()
        End If
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Timer1.Stop()
        TimbreTB(a).BackColor = Color.Red
        IPTB(a).BackColor = Color.Red
        AxWinsockState.Close()
        State()
    End Sub
End Class

