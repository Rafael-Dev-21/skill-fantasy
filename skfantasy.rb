#!/usr/bin/env ruby

require_relative 'src/engine'

game = Engine.new(ARGV[0])

game.run

game.close
