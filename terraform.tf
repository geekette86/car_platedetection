resource "null_resource" "default" {
  provisioner "local-exec" {
    command = "echo 'may the force be with us'"
  }
}
