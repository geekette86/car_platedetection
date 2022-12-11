resource "null_resource" "default" {
  provisioner "local-exec" {
    command = var.message
  }
}
