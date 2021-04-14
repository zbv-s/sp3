FROM ubuntu
ENV TZ=Europe/Kiev
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update -y && apt-get install build-essential gcc-multilib nano -y
RUN apt-get install gcc-multilib g++-multilib -y
COPY lr3.cpp .
RUN g++ -m32 lr3.cpp -o lr3
CMD ./lr3


