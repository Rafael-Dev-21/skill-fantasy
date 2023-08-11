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

    @map = Map.new(16, 2)
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
    when 'd' then
      @debug = !@debug
    end

    @player.move(newpos)
    Async { @map.check_chunks newpos }
  end

  def input
    @curr_input = getch
  end

  def run
    if @view.ok
      while @curr_input != 'q'
        input
        update
        @view.game self
      end
    end
  end

  def close
    @view.close
  end
end
