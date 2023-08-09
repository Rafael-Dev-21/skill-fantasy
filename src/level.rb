require 'async'

require_relative 'noise'

class Tile
  attr_accessor :char, :color, :type, :walkable

  def initialize(type)
    @type = type

    @walkable = true

    case @type
    when :grass then
      @char = ','
      @color = 1
    when :sand then
      @char = '~'
      @color = 2
    when :water then
      @char = '~'
      @color = 3
    when :mountain then
      @char = '^'
      @color = 4
      @walkable = false
    else
      @char = ' '
      @color = 0
    end
  end
end

def get_tile(elevation)
  if elevation < 0.1
    :water
  elsif elevation < 0.2
    :sand
  elsif elevation < 0.5
    :grass
  else
    :mountain
  end
end

class Map
  attr_accessor :width, :height, :tiles, :spawn

  def initialize(size = 32, radius = 2)
    Sync do
      @size = size
      @radius = radius

      if @size < 2 || @size % 2 != 0
        @size = 32
      end

      if @radius < 1
        @radius = 2
      end

      @spawn = nil

      @noise = Noise.new

      @tiles = {}

      @chunk_names = {}

      Async { gen_initial }
    end
  end

  def tile_at(y, x)
    @tiles[index(y, x)]
  end

  def check_chunks(point)
    y = point.y / @size
    x = point.x / @size
    Async do
      ((y - @radius)..(y + @radius)).each { |j|
        ((x - @radius)..(x + @radius)).each { |i|
          gen_chunk(j, i)
        }
      }
    end
  end

  private

  def gen_initial
    gen_chunk(0, 0)

    x = y = 1
    while not @spawn do
      [-y, y].each {|j|
        [-x, x].each { |i|
          gen_chunk(j, i)
        }
      }
    end

    check_chunks(@spawn)
  end

  def gen_chunk(chunky, chunkx)
    name = index(chunky, chunkx)

    return if @chunk_names[name]

    @chunk_names[name] = true

    Async do
      starty = chunky * @size
      startx = chunkx * @size
      endy = (chunky + 1) * @size
      endx = (chunkx + 1) * @size
      
      (starty..endy).each do |y|
        (startx..endx).each do |x|
          ny = y.to_f / @size - 0.5
          nx = x.to_f / @size - 0.5

          e = (@noise.fbm(nx, ny, 1, 3) * 1.2) ** 2.75

          type = get_tile e

          if type == :grass and not @spawn
            @spawn = Point.new(y, x)
          end

          @tiles[index(y, x)] = Tile.new type
        end
      end
    end
  end

  def index(y, x)
    "#{x.to_s},#{y.to_s}"
  end
end
