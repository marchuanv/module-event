file(REMOVE_RECURSE
  "libShared.a"
  "libShared.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/Shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
