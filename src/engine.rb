require 'curses'

require_relative 'geom'
require_relative 'entity'
require_relative 'level'
require_relative 'view'

class Engine
  include Curses

  attr_accessor :player, :map, :curr_input, :view, :debug

  def initialize(debug = false)
    @debug = debug

    @map = Map.new()
    startpos = @map.spawn.dup

    @player = Entity.new(startpos, '@', 5)
    @curr_input = ''
    @view = View.new @player.pos
  end

  def update
    newpos = @player.pos.dup

    case @curr_input
    when 'k' then
      newpos.y -= 1
    when 'j' then
      newpos.y += 1
    when 'h' then
      newpos.x -= 1
    when 'l' then
      newpos.x += 1
    end

    if @map.tile_at(newpos.y, newpos.x).type != :mountain
      @player.move(newpos)
      @map.check_chunks newpos
    end
  end

  def input
    @curr_input = getch
  end

  def run
    if @view.ok
      while @curr_input != 'q'
        update
        @view.game self
        input
      end
    end
  end

  def close
    @view.close
  end
end
