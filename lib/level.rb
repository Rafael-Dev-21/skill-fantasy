require 'async'

require_relative 'noise'

class Tile
  attr_accessor :char, :color, :type, :biome

  def initialize(type, biome)
    @type = type
    @biome = biome

    case @type
    when :grass then
      @char = ','
      case @biome
      when :forest then
        @color = 6
      when :tundra then
        @color = 7
      else
        @color = 1
      end
    when :sand then
      @char = '~'
      @color = 2
    when :water then
      @char = '~'
      @color = 3
    when :stone then
      @char = '.'
      @color = 4
    else
      @char = ' '
      @color = 0
    end
  end
end

def get_tile(elevation, biome)
  if elevation < 0.2
    :water
  elsif elevation < 0.3
    :sand
  elsif elevation < 0.6
    if biome == :desert
      :sand
    else
      :grass
    end
  else
    :stone
  end
end

def get_biome(moisture, temperature)
  if temperature > 0.5
    if moisture < 0.3
      return :desert
    end

    if moisture < 0.5
      return :plains
    end

    return :forest
  end

  if temperature > 0.3
    if moisture < 0.2
      return :desert
    end
    return :plains
  end

  if moisture < 0.1
    return :desert
  end

  if moisture < 0.2
    return :plains
  end

  return :tundra
end

class Map
  attr_accessor :tiles, :spawn

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

      @noise = Perlin.new

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

          e = @noise.value(nx, ny)
          m = @noise.value(nx + 1, ny)
          t = @noise.value(nx, ny + 1)

          biome = get_biome(m, t)
          type = get_tile(e, biome)

          if type != :water and not @spawn
            @spawn = Point.new(y, x)
          end

          @tiles[index(y, x)] = Tile.new(type, biome)
        end
      end
    end
  end

  def index(y, x)
    "#{x.to_s},#{y.to_s}"
  end
end
