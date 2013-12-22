notification :off

guard :shell do
  watch(/(.*)\.(c|h)$/) { rake :build }
  watch(/(.*)\.rb$/) { rake }
end

def rake(*args)
  system("rake #{args.join(" ")}")
end