Imports System
Imports System.Net
Imports System.Net.Sockets
Imports System.Threading
Imports System.Text
Imports System.IO


Public Class Principal

    Inherits System.Windows.Forms.Form
    Dim Carga As Integer
    Dim Envios As Integer
    Dim Acc As Integer
    Dim Sended As Boolean
    Dim data(50) As Object
    Dim Prob As Integer
    Dim Cant As Integer
    Dim CantB As Integer
    Dim Reci As Object
    Dim Recibi As String
    Dim primero As Boolean

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Borrar.Click
        While ASetear.CheckedItems.Count > 0
            ASetear.Items.Remove(ASetear.CheckedItems(0))
        End While
    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles BorrarTodo.Click
        ASetear.Items.Clear()
    End Sub

    Private Sub ComboBox3_SelectedIndexChanged(sender As Object, e As EventArgs) Handles Timbres1.SelectedIndexChanged
        Acc = 1
        Prob = 1
        Try
            AxWinsock1.Close()
        Catch ex As Exception

        End Try
        If Timbres1.SelectedIndex <> 0 Then
                AxWinsock1.RemoteHost = My.Settings.IP.Item(My.Settings.Timbre.IndexOf(Timbres1.SelectedItem.ToString))
            'Determino a donde se quiere conectar el usuario
            AxWinsock1.RemotePort = Convert.ToInt32(My.Settings.Puertos.Item(My.Settings.Timbre.IndexOf(Timbres1.SelectedItem.ToString)))
            AxWinsock1.Connect()
            Exportar.Text() = "Conectando"
            Exportar.Enabled = False
            Timer1.Start()
            Timbres2.SelectedItem() = My.Settings.IP.Item(My.Settings.Timbre.IndexOf(Timbres1.SelectedItem.ToString))
            End If
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Exportar.Click
        Sended = True
        Progress.Minimum = 0
        Progress.Maximum = ASetear.CheckedItems.Count
        Progress.Value = 0
        Carga = 0
        Tipo = 1
        Envios = 0
        For j As Integer = 0 To 50
            data.SetValue(Nothing, j)
        Next
        Try
            While ASetear.CheckedItems.Count > 0
                data(Carga) = Encoding.ASCII.GetBytes(("Set   ") & ("LUN") & (" ") & ASetear.CheckedItems(0) & (";"))
                ASetear.Items.Remove(ASetear.CheckedItems(0))
                Carga = Carga + 1
            End While
            Enviar()
        Catch ex As Exception
            MsgBox("No se ha podido setear el horario en el dispositivo seleccionado", MsgBoxStyle.Critical)
        End Try
    End Sub

    Private Sub BtnAct_Click(sender As Object, e As EventArgs) Handles BtnAct.Click
        Actualizar()
    End Sub

    Private Sub BtnQuitar_Click(sender As Object, e As EventArgs) Handles Quitar.Click
        Carga = 0
        Envios = 0
        Sended = True
        Progress.Maximum = Seteados.CheckedItems.Count
        For j As Integer = 0 To 50
            data.SetValue(Nothing, j)
        Next
        Try
            While Seteados.CheckedIndices.Count > 0
                data(Carga) = Encoding.ASCII.GetBytes(("Borrar") & ("LUN") & (" ") & Seteados.CheckedIndices(Seteados.CheckedIndices.Count - 1) & (";"))
                Seteados.Items.Remove(Seteados.CheckedItems(Seteados.CheckedIndices.Count - 1))
                Carga = Carga + 1
            End While
            Enviar()
        Catch ex As Exception
            MsgBox("No se ha podido borrar el horario en el dispositivo seleccionado", MsgBoxStyle.Critical)
        End Try
    End Sub

    Private Sub Vacaciones_Click(sender As Object, e As EventArgs) Handles Vacaciones.Click
        AxWinsock1.Close()
        Acc = 2
        Carga = 1
        AxWinsock1.RemoteHost = My.Settings.IP.Item(Carga)
        With AxWinsock1
            .RemotePort = 35
            'Me conecto
            .Connect()
        End With
        Timer1.Start()
    End Sub

    Private Sub Principal_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timbres1.DataSource = My.Settings.Timbre
        Timbres2.DataSource = My.Settings.Timbre
    End Sub

    Private Sub LibresToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LibresToolStripMenuItem.Click
        Libres.Show()
    End Sub

    Private Sub Principal_FormClosing(sender As Object, e As FormClosingEventArgs) Handles MyBase.FormClosing
        If My.Settings.Users.Count = 0 Then
            My.Settings.Users.Add("Admin")
            My.Settings.Pass.Add("Root")
            My.Settings.Save()
            MsgBox("La lista de usuarios quedo vacia, se agrego usuario Admin contraseña Root")
        End If
    End Sub

    Private Sub AxWinsock1_DataArrival(sender As Object, e As AxMSWinsockLib.DMSWinsockControlEvents_DataArrivalEvent) Handles AxWinsock1.DataArrival
        If (Tipo = 1) Then
            CheckForIllegalCrossThreadCalls = False
            AxWinsock1.GetData(Reci)
            Recibi = Encoding.ASCII.GetString(Reci)
            Seteados.Items.Add(item:=Recibi, isChecked:=False)
            AxWinsock1.SendData("OK;")
        Else
            AxWinsock1.GetData(Reci)
        End If
    End Sub

    Private Sub AxWinsock1_ConnectEvent(sender As Object, e As EventArgs) Handles AxWinsock1.ConnectEvent
        Exportar.Text = "Exportar cambios >"
        Exportar.Enabled = True
        Timer1.Stop()
        Select Case Acc
            Case 1
                Actualizar()
            Case 2
                Try
                    data(0) = Encoding.ASCII.GetBytes("Vac   ;")
                    AxWinsock1.SendData(data(0))
                Catch ex As Exception
                    MsgBox("No se ha podido configurar el dispositivo en modo vacaciones")
                End Try
        End Select

    End Sub

    Private Sub AxWinsock1_SendComplete(sender As Object, e As EventArgs) Handles AxWinsock1.SendComplete
        If sended = True Then
            Enviar()
        End If
        If Acc = 2 Then
            AxWinsock1.Close()
            Timbres1.SelectedIndex() = 0
            Timbres2.SelectedIndex = 0
            Seteados.Items.Clear()
            Vacacion()
        End If
    End Sub

    Public Sub Vacacion()
        If Carga < My.Settings.IP.Count - 1 Then
            Carga = Carga + 1
            AxWinsock1.RemoteHost = My.Settings.IP.Item(Carga)
            With AxWinsock1
                .RemotePort = 35
                'Me conecto
                .Connect()
            End With
            Timer1.Start()
        End If
    End Sub

    Public Sub Actualizar()
        Tipo = 1
        Envios = 0
        Sended = False
        Progress.Maximum() = 1
        Seteados.Items.Clear()
        For j As Integer = 0 To 50
            data.SetValue(Nothing, j)
        Next
        data(0) = Encoding.ASCII.GetBytes("Act   ;")
        Enviar()
    End Sub

    Public Sub Silencio()
        Carga = 0
        Envios = 0
        Sended = True
        Progress.Maximum = Seteados.CheckedItems.Count
        For j As Integer = 0 To 50
            data.SetValue(Nothing, j)
        Next
        Try
            While Seteados.CheckedIndices.Count > 0
                data(Carga) = Encoding.ASCII.GetBytes(("Sil   ") & ("LUN") & (" ") & Seteados.CheckedIndices(Seteados.CheckedIndices.Count - 1) & (" ") & (Silenciar.Dias.Text) & (";"))
                Seteados.SetItemCheckState(Seteados.CheckedIndices(Seteados.CheckedIndices.Count - 1), CheckState.Unchecked)
                Carga = Carga + 1
            End While
            Enviar()
        Catch ex As Exception
            MsgBox("No se ha podido silenciar el horario en el dispositivo seleccionado", MsgBoxStyle.Critical)
        End Try
    End Sub

    Public Sub Dessilencio()
        Carga = 0
        Envios = 0
        Sended = True
        Progress.Maximum = Seteados.CheckedItems.Count
        For j As Integer = 0 To 50
            data.SetValue(Nothing, j)
        Next
        Try
            While Seteados.CheckedIndices.Count > 0
                data(Carga) = Encoding.ASCII.GetBytes(("Sil   ") & ("LUN") & (" ") & Seteados.CheckedIndices(Seteados.CheckedIndices.Count - 1) & (" ") & ("00") & (";"))
                Seteados.SetItemCheckState(Seteados.CheckedIndices(Seteados.CheckedIndices.Count - 1), CheckState.Unchecked)
                Carga = Carga + 1
            End While
            Enviar()
        Catch ex As Exception
            MsgBox("No se ha podido desilenciar el horario en el dispositivo seleccionado", MsgBoxStyle.Critical)
        End Try
    End Sub

    Private Sub Enviar()
        Try
            If IsNothing(data(Envios)) <> True Then
                AxWinsock1.SendData(data(Envios))
                Envios = Envios + 1
                Progress.Value = Envios
                Thread.Sleep(200)
            Else
                Actualizar()
            End If
        Catch e As Exception
            MsgBox("No se puedo realizar el envio de datos al dispositivo")
        End Try

    End Sub

    Private Sub TimbresToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles TimbresToolStripMenuItem.Click
        AdmnTimb.Show()
    End Sub

    Private Sub AcercaDeToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AcercaDeToolStripMenuItem.Click
        AcercaDe.Show()
    End Sub


    Private Sub AgregarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AgregarToolStripMenuItem.Click
        Añadir.Show()
    End Sub

    Private Sub ModificarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ModificarToolStripMenuItem.Click
        Modificar.Show()
    End Sub

    Private Sub DuracionToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles DuracionToolStripMenuItem.Click
        Duracion.Show()
    End Sub

    Private Sub BorrarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles BorrarToolStripMenuItem.Click
        Delete.Show()
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Agregar.Click
        Seteos.Show()
    End Sub

    Private Sub HoraToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FechaHora.Click
        HoraYFecha.Show()
    End Sub

    Private Sub Button1_Click_1(sender As Object, e As EventArgs) Handles Silenc.Click
        Silenciar.Show()
    End Sub

    Private Sub Estado_Click(sender As Object, e As EventArgs) Handles Estado.Click
        EstadoForm.Show()
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Timer1.Stop()
        Exportar.Text = "Exportar cambios >"
        Exportar.Enabled = True
        If Prob = 1 Then
            MsgBox("No se ha podido conectar al dispositivo", MsgBoxStyle.Critical)
            Timbres1.SelectedItem() = 0
            Timbres2.SelectedIndex() = 0
            Prob = 2
        End If
        If Acc = 2 Then
            AxWinsock1.Close()
            Vacacion()
        End If
    End Sub

End Class
