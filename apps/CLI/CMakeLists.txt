add_executable(nobridge
  main.cpp
)

target_link_libraries(nobridge
  PRIVATE 
  mika
  adapter
  engine
  pbn
  storage
  vmath
)

set_target_properties(nobridge PROPERTIES FOLDER "apps/CLI")


