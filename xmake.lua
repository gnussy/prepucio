set_project("prepucio")
set_version("1.1.1")
set_xmakever("2.7.0")

set_languages("c++20")
add_rules("mode.debug", "mode.release")

local libs = { "fmt", "penis", "tabulate" }

add_includedirs("include")
add_requires(table.unpack(libs))

target("prepucio-lib")
  set_kind("headeronly")
  add_packages(table.unpack(libs))

-- Define a function to get all files in a directory
function get_files_in_directory(dir)
    local files = os.files(path.join(dir, "*.c"))
    for _, f in ipairs(os.files(path.join(dir, "*.cpp"))) do
        table.insert(files, f)
    end
    return files
end

-- Define a target for every file in the example directory
local example_dir = "examples"
for _, file in ipairs(get_files_in_directory(example_dir)) do
  local target_name = path.basename(file)
  target_name = target_name:gsub("%.[^.]+$", "") -- remove file extension
  target("example_" .. target_name)
    set_default(false)
    set_kind("binary")
    add_files(file)
    add_packages(table.unpack(libs))
    add_deps("prepucio-lib")
end

add_installfiles("(include/**)", {prefixdir = ""})
