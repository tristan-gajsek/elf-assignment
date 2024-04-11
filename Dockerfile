FROM ubuntu:latest

RUN apt-get update -y && apt-get install -y gcc-multilib make

WORKDIR /code
COPY . .

CMD ["make"]
