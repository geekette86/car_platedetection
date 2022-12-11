resource "null_resource" "default" {
  provisioner "local-exec" {
    command = " may the force be with us"
  }
}
