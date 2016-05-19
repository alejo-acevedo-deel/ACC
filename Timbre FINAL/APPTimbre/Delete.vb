Public Class Delete

    ' TODO: Insert code to perform custom authentication using the provided username and password 
    ' (See http://go.microsoft.com/fwlink/?LinkId=35339).  
    ' The custom principal can then be attached to the current thread's principal as follows: 
    '     My.User.CurrentPrincipal = CustomPrincipal
    ' where CustomPrincipal is the IPrincipal implementation used to perform authentication. 
    ' Subsequently, My.User will return identity information encapsulated in the CustomPrincipal object
    ' such as the username, display name, etc.

    Private Sub OK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OK.Click
        Dim Ind As Integer
        Try
            Ind = My.Settings.Users.IndexOf(ComboBox1.SelectedItem.ToString)
            If (My.Settings.Pass.Item(Ind) = PasswordTextBox.Text) Then
                My.Settings.Users.RemoveAt(Ind)
                My.Settings.Pass.RemoveAt(Ind)
                My.Settings.Save()
                My.Settings.Reload()
                ComboBox1.DataSource = My.Settings.Users
                PasswordTextBox.Text = ""
            Else
                MsgBox("Password Incorrecta", MsgBoxStyle.Critical)
            End If

        Catch ex As Exception
            MsgBox("Usuario Incorrecto", MsgBoxStyle.Critical)
        End Try
    End Sub

    Private Sub Cancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Cancel.Click
        Me.Close()
    End Sub

    Private Sub login_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        ComboBox1.DataSource = My.Settings.Users
    End Sub
End Class
