# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure(2) do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://atlas.hashicorp.com/search.
  config.vm.box = 'puppetlabs/centos-7.2-64-puppet'


  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  # config.vm.box_check_update = false

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # config.vm.network "forwarded_port", guest: 80, host: 8080

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  # config.vm.provider "virtualbox" do |vb|
  #   # Display the VirtualBox GUI when booting the machine
  #   vb.gui = true
  #
  #   # Customize the amount of memory on the VM:
  #   vb.memory = "1024"
  # end
  #
  # View the documentation for the provider you are using for more
  # information on available options.

  # Define a Vagrant Push strategy for pushing to Atlas. Other push strategies
  # such as FTP and Heroku are also available. See the documentation at
  # https://docs.vagrantup.com/v2/push/atlas.html for more information.
  # config.push.define "atlas" do |push|
  #   push.app = "YOUR_ATLAS_USERNAME/YOUR_APPLICATION_NAME"
  # end

  # Enable provisioning with a shell script. Additional provisioners such as
  # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
  # documentation for more information about their specific syntax and use.
  # config.vm.provision "shell", inline: <<-SHELL
  #   sudo apt-get update
  #   sudo apt-get install -y apache2
  # SHELL
  config.vm.provision "shell", inline: <<-SHELL
    yum install -y yum-utils yum-plugin-auto-update-debug-info
    yum install -y https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
    yum install -y cmake3 gcc gcc-c++ bison flex glib2-devel lcov soci-devel soci-mysql boost-\* valgrind nano lsof
    yum install -y http://dl.fedoraproject.org/pub/fedora/linux/development/rawhide/Everything/x86_64/os/Packages/g/gcovr-3.3-4.fc27.noarch.rpm
    yum install -y https://dev.mysql.com/get/mysql57-community-release-el7-9.noarch.rpm
    yum install -y mysql-community-server
    debuginfo-install -y glib2 soci soci-mysql boost\* mysql-community-server
    grep -q includedir /etc/my.cnf || echo '!includedir /etc/my.cnf.d' >> /etc/my.cnf
    cat > /etc/my.cnf.d/binlog.cnf <<EOF
[mysqld]
server-id = 1
log-bin		= /var/lib/mysql/mysql-bin.log
log-bin-index 	= /var/lib/mysql/mysql-bin.index
expire-logs-days        = 30
max_binlog_size         = 104857600
EOF
    [ -f /var/lib/mysql/auto.cnf ] || mysqld --initialize-insecure --user=mysql
    systemctl enable mysqld
    systemctl restart mysqld
    exit 0
  SHELL
  config.vm.provision "shell", privileged: false, inline: <<-SHELL
    mkdir -p build
    cd build
    cmake3 /vagrant/ -Dtest=ON -Dcoverage=ON -DCMAKE_BUILD_TYPE=Debug
  SHELL
end
