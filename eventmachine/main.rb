#!/usr/bin/env ruby
require 'bundler'
require './role'

Bundler.require

class TankWarServer  < EM::Connection
  #@@connected_clients = Array.new
  @@roles = Array.new
  
  def post_init
    #@@connected_clients.push(self)
    role = Role.new
    role.socket = self
    @@roles.push role
    ap "-- someone connected to the echo server! #{@@roles.size}"
    port, ip = Socket.unpack_sockaddr_in(get_peername)
    ap "got from #{ip}:#{port}"

  end

  def receive_data data
    ap data
    send_data data
    close_connection if data =~ /quit/i
  end

  def unbind
    #@@connected_clients.delete(self)
    @@roles.delete_if {|role| role.socket == self}
    ap "-- someone disconnected ! #{@@roles.size}"
  end

   def other_peers
     #@@connected_clients.reject { |c| self == c }
   end # other_peers

end

# Note that this will block current thread.
EventMachine.run {
  EventMachine.start_server "0.0.0.0", 4321, TankWarServer
}
