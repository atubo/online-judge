require 'set'

class Disk
  include Comparable
  attr_accessor :name, :folders
  def initialize(name)
    @name = name
    @folders = Hash.new
  end
  def <=> (other)
    self.name <=> other.name
  end
end

class Folder
  include Comparable
  attr_accessor :name, :folders, :file_num, :total_file_num, :total_folder_num
  def initialize(name)
    @name = name
    @folders = Hash.new
    @file_num = 0 #direct decendant
    @total_file_num = 0
    @total_folder_num = 0
  end
  def <=> (other)
    self.name <=> other.name
  end
  def stat()
    @folders.each do |folder_name, folder|
      (fd_num, fl_num) = folder.stat
      @total_folder_num += fd_num
      @total_file_num   += fl_num
    end
    return @total_folder_num + @folders.size, @total_file_num + @file_num
  end
end

class Solution
  def initialize()
    @disks = Hash.new
    while line = gets do
      disk_name = line[0,1]
      if @disks.has_key?(disk_name)
        disk = @disks[disk_name]
      else
        disk = Disk.new(disk_name)
        @disks[disk_name] = disk
      end
      line = line[2..-1]
      parse(disk, line)
    end
  end

  def parse(location, line)
    match_data = /\\(.*?)\\/.match(line)
    if match_data.nil?
      location.file_num += 1
    else
      folder_name = match_data[1]
      if location.folders.has_key?(folder_name)
        folder = location.folders[folder_name]
      else
        folder = Folder.new(folder_name)
        location.folders[folder_name] = folder
      end
      line = line[match_data[0].size-1..-1]
      parse(folder, line)
    end
  end

  def solve()
    fd_max = 0
    fl_max = 0
    @disks.each_value do |disk|
      disk.folders.each do |folder_name, folder|
        fd_num, fl_num = folder.stat
        fd_max = [fd_max, fd_num].max
        fl_max = [fl_max, fl_num].max
      end
    end
    printf("%d %d\n", fd_max, fl_max)
  end
end

solution = Solution.new
solution.solve

