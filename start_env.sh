sed -i -e -E "s/([0-9]{1,3}\.){3}[0-9]{1,3}/ARG/g" ./docker-compose.yml
docker-compose down
docker rmi minirt_minirt
ARG=$(ifconfig en0 | grep inet | grep -v inet6 | awk '{print $2}')
sed -ie "s/ARG/$ARG/g" ./docker-compose.yml
docker build .
docker-compose up -d --build
docker attach develop_space
