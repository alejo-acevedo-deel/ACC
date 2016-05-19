Public Class AdmnTimb

    ' TODO: Insert code to perform custom authentication using the provided username and password 
    ' (See http://go.microsoft.com/fwlink/?LinkId=35339).  
    ' The custom principal can then be attached to the current thread's principal as follows: 
    '     My.User.CurrentPrincipal = CustomPrincipal
    ' where CustomPrincipal is the IPrincipal implementation used to perform authentication. 
    ' Subsequently, My.User will return identity information encapsulated in the CustomPrincipal object
    ' such as the username, display name, etc.

    Private Sub OK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        Me.Close()
    End Sub

    Private Sub Cancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        Me.Close()
    End Sub

    Private Sub UsernameLabel_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub LoginForm1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        ComboBox1.DataSource = My.Settings.Timbre
        ComboBox2.DataSource = My.Settings.Timbre

    End Sub

    Private Sub btnModificar_Click(sender As Object, e As EventArgs) Handles btnModificar.Click
        My.Settings.Timbre.Item(ComboBox1.SelectedIndex) = txtBoxNamMod.Text
        My.Settings.IP.Item(ComboBox1.SelectedIndex) = txtboxIPMod.Text
        My.Settings.Puertos.Item(ComboBox1.SelectedIndex) = TextBox2.Text
        My.Settings.Save()
        My.Settings.Reload()
        Principal.Timbres1.DataSource = My.Settings.Timbre
        Principal.Timbres2.DataSource = My.Settings.Timbre
    End Sub

    Private Sub btnAgregar_Click(sender As Object, e As EventArgs) Handles btnAgregar.Click
        My.Settings.Timbre.Add(txtBoxNamAdd.Text)
        My.Settings.IP.Add(txtBoxIPAdd.Text)
        My.Settings.Puertos.Add(TextBox1.Text)
        My.Settings.Save()
        My.Settings.Reload()
        Principal.Timbres1.DataSource = My.Settings.Timbre
        Principal.Timbres2.DataSource = My.Settings.Timbre
        ComboBox1.DataSource = My.Settings.Timbre
        ComboBox2.DataSource = My.Settings.Timbre
    End Sub

    Private Sub ComboBox2_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox2.SelectedIndexChanged
        txtBoxIPQui.Text = My.Settings.IP.Item(ComboBox2.SelectedIndex)
        TextBox3.Text = My.Settings.Puertos.Item(ComboBox2.SelectedIndex)
    End Sub

    Private Sub btnBorrar_Click(sender As Object, e As EventArgs) Handles btnBorrar.Click
        My.Settings.Timbre.Remove(My.Settings.Timbre.Item(ComboBox2.SelectedIndex))
        My.Settings.IP.Remove(My.Settings.IP.Item(ComboBox2.SelectedIndex))
        My.Settings.Save()
        My.Settings.Reload()
        Principal.Timbres1.DataSource = My.Settings.Timbre
        Principal.Timbres2.DataSource = My.Settings.Timbre
        ComboBox1.DataSource = My.Settings.Timbre
        ComboBox2.DataSource = My.Settings.Timbre
    End Sub

    Private Sub Cancel_Click_1(sender As Object, e As EventArgs) Handles Cancel.Click
        Me.Close()

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Me.Close()

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Me.Close()
    End Sub
End Class
