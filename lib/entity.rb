
require_relative 'geom'

class Entity
  attr_accessor :pos, :char, :color

  def initialize(pos, char, color)
    @pos = pos
    @char = char
    @color = color
  end

  def move(pos)
    @pos.x = pos.x
    @pos.y = pos.y
  end
end

