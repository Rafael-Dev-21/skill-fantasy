require 'curses'

require_relative './level'
require_relative './entity'
require_relative './geom'

class View
  include Curses

  attr_accessor :center, :ok

  def initialize(pos)
    @center = pos

    init_screen
    noecho
    curs_set 0
    Curses.timeout = 0

    if !colors?
      close_screen

      puts "no colors!"

      @ok = false
    else
      @ok = true
    end
  end

  def entity(entity)
    y = entity.pos.y - gety
    x = entity.pos.x - getx

    if y > 0 && lines > y && x  > 0 && cols > x
      setpos(y, x)
      attrset(color_pair(entity.color))
      addstr(entity.char)
      attrset(color_pair(0))
    end
  end

  def map(map)
    (0..lines).each do |y|
      (0..cols).each do |x|
        mapy = y + gety
        mapx = x + getx

        setpos(y, x)
        tile = map.tile_at(mapy, mapx)
        attrset(color_pair(tile.color))
        addstr(tile.char)
        attrset(color_pair(0))
      end
    end
  end

  def game(game)
    map game.map
    entity game.player

    if game.debug
      5.times { |i|
        setpos(i, 0)
        addstr(" " * 10)
      }

      setpos(0, 0)
      addstr("res=#{cols}x#{lines}")
      setpos(1, 0)
      addstr("#{game.player.pos}")

      begin
        y = game.player.pos.y
        x = game.player.pos.x
        tile = game.map.tile_at(y, x)
        setpos(2, 0)
        addstr(":#{tile.biome}")
      end
    end

    refresh
  end

  def close
    close_screen
  end

  private

  def colors?
    if !Curses.has_colors?
      false
    else
      start_color

      init_pair(1, 3, 2)
      init_pair(2, 3, 230)
      init_pair(3, 14, 12)
      init_pair(4, 0, 8)
      init_pair(5, 1, 5)
      init_pair(6, 3, 22)
      init_pair(7, 3, 73)

      true
    end
  end

  def gety
    @center.y - lines / 2
  end

  def getx
    @center.x - cols / 2
  end
end
