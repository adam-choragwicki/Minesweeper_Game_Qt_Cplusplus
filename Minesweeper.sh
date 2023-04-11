xhost +local:docker

if [[ "$(docker images -q minesweeper 2> /dev/null)" == "" ]]; then
  docker build -t minesweeper .
fi

docker run -d --rm --env="DISPLAY" --net=host minesweeper

