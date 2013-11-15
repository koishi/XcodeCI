# specify your Xcode project and workspace if needed
$INFOPLIST_FILES = `find . -name "*-Info.plist" 2>/dev/null`.split("\n")
$PROJECT = `find *.xcodeproj -maxdepth 0 2>/dev/null`.split("\n").first
$WORKSPACE = `find *.xcworkspace -maxdepth 0 2>/dev/null`.split("\n").first
# extract active schemes
$SCHEMS = \
`find . -name "*.xcscheme" 2>/dev/null`
  .split("\n")
  .map{ |s| s = File.basename(s).gsub(/\.xcscheme/,"")}
$TARGETS = \
`cat #{$PROJECT}/project.pbxproj`
  .gsub("\n","")
  .scan(/targets = \(.+?\)/)
  .first
  .scan(/\/\* (.+?) \*\//)
  .map{ |e| e = e.first}
# extract configurations from project file
$CONFIGURATIONS = \
`cat #{$PROJECT}/project.pbxproj`
  .gsub("\n","")
  .scan(/buildConfigurations = \(.+?\);/)
  .first
  .scan(/\/\* (.+?) \*\//)
  .map { |e| e = e.first }
# update types
$UPDATES = ["major","minor","patch"]

task :default => "extract"
task :extract do
  print "InfoPlist:\t"
  p $INFOPLIST_FILES
  print "Project:\t"
  p $PROJECT
  print "Workspace:\t"
  p $WORKSPACE
  print "Schemes:\t"
  p $SCHEMS
  print "Targets:\t"
  p $TARGETS
  print "Configurations:\t"
  p $CONFIGURATIONS
  print "Update Levels:\t"
  p $UPDATES
end

task :setup do
  # check if Homebre has been installed
  `[[ -f which brew ]]`
  # xctool
  `[[ -f which xctool]]`
end

# build application
# usage
# build
# build:SCHEME
# build:CONFIGURATION
# build:SCHEME:CONFIGURATION
task :build => "build:default"
namespace :build do
  task :default do
    system "xctool build -project #{$PROJECT} -scheme #{$SCHEMS.first}"
  end
  task :all do
    $SCHEMS.each do |scheme|
      system "xctool build -project #{$PROJECT} -scheme #{scheme}"
    end
  end
  # dynamic task definition
  $SCHEMS.each do |scheme|
    # define `build:SCHEME` task
    task "#{scheme}" do
      system "xctool build -project #{$PROJECT} -scheme #{scheme}"
    end
    $CONFIGURATIONS.each do |configuration|
      # define `build:CONFIGURATION` task
      task "#{configuration}" do
        system "xtool build -project #{$PROJECT} -scheme #{$SCHEMS.first} -configuration #{configuration}"
      end
      # dfine `build:SCHEME:CONFIGURATION` task
      task "#{scheme}:#{configuration}" do
        system "xctool build -project #{$PROJECT} -scheme #{scheme} -configuration #{configuration}"
      end
    end
    task :test => "test:all"
    namespace :test do
      def build_test(scheme)
        system "xctool build-tests -sdk iphonesimulator -project #{$PROJECT} -scheme #{scheme}"
      end
      task :all do
        $SCHEMS.each do |scheme|
          build_test(scheme)
        end
      end
      $SCHEMS.each do |scheme|
        task "#{scheme}" do
          build_test(scheme)
        end
      end
    end
  end
end

# run tests
task :test => "test:all"
namespace :test do
  def test(scheme)
    system "xctool run-tests -sdk iphonesimulator -project #{$PROJECT} -scheme #{scheme}"
  end
  task :all do
    $SCHEMS.each do |scheme|
      test(scheme)
    end
  end
  $SCHEMS.each do |scheme|
    task "#{scheme}" do
      test(scheme)
    end
  end
end

# clean project
# usage
# clean
# clean:all
# clean:SCHEME
task :clean => "clean:all"
namespace :clean do
  task :all do
    $SCHEMS.each do |scheme|
      system "xctool clean -project #{$PROJECT} -scheme #{scheme}"
    end
  end
  # dynamicallly run task with scheme name
  $SCHEMS.each do |scheme|
    task scheme do
      system "xctool clean -project #{$PROJECT} -scheme #{scheme}  -sdk iphonesimulator"
    end
  end
end

# usage
# options
# -ib => increment build number (CFBundleVersion)
# -iv => increment version number (CFBundleShortVersionString)
#

namespace :archive do |t, args|
  $SCHEMS.each do |scheme|
    task "#{scheme}" do
    end
    $UPDATES.each do |update|
      task "#{update}" do |task|
        increment_version_number(scheme,update)
        increment_build_number(scheme)
      end
      # system "xctool archive -project #{$PROJECT} -scheme #{scheme}"
    end
  end
  def get_plist_path (scheme)
  # extract Info.plist file with scheme name
  plist = $INFOPLIST_FILES.find{ |file| file.match "#{scheme}-Info.plist" }
  end

  def get_version_number (scheme)
    # get version
    version = \
    `/usr/libexec/PlistBuddy -c \"Print CFBundleShortVersionString\" \"#{get_plist_path(scheme)}\"`
      .gsub("\n","")
      .to_s
      .split(".")
    # => x.x.x
    if version.length < 3
      until version.length == 3
        version << "0"
      end
    end
    p version
    version.join(".")
  end

  def increment_version_number (scheme,update)
    # increment version number
    index = $UPDATES.index(update)
    version = get_version_number(scheme).split(".")
    version[index] = "#{version[index].to_i + 1}"
    for i in index+1..$UPDATES.length-1
      version[i] = "0"
    end
    version = version.join(".")
    write_to_plist \
      get_plist_path(scheme),
      "CFBundleShortVersionString",
      version
    return version
  end

  def increment_build_number (scheme)
    bn = get_version_number(scheme)+" "+`date "+%Y%m%d%H%M"`
    write_to_plist \
      get_plist_path(scheme),
      "CFBundleVersion",
      bn
    return bn
  end

  def write_to_plist(plist,key,value)
    `/usr/libexec/PlistBuddy -c "Set :#{key} #{value}" "#{plist}"`
  end
end