# twitApp

## О проекте

В программе присутствуют 2 раздела:

"User information" показывает информацию о конкретном пользователе (username вводится в соответствующее поле), список подписчиков и друзей (в одном блоке максимум 200 человек, для перехода к следующему или предыдущему используются стрелочки вправо или влево соответственно);

"Followers intersection" выводит общих подписчиков и друзей у двух пользователей.

***

Проект реализован при помощи фреймворка Qt и библиотеки twitCurl, которая в свою очередь построена на библиотеке cURL. TwitCurl была использована из-за удобства работы с Twitter API.

***

Для сборки проекта использовались:

* Qt Creator 4.1.0, основанный на Qt 5.7.0 <https://www.qt.io/download-open-source/>
* библиотека cURL <https://curl.haxx.se/download.html>
* немного измененная библиотека twitCurl <https://github.com/bindasov/twitcurl/tree/master/libtwitcurl> (одно изменение пришлось сделать из-за того, что в Twitter API изменились адресы для запросов, а библиотеку не обновили)

***

Сборка cURL

```
Распаковать архив
cd /path/to/cURL/
./configure --with-ssl (или ./configure --with-darwinssl)
make
make test (optional)
make install
```

Сборка twitCurl
```
git clone https://github.com/bindasov/twitcurl/tree/master/libtwitcurl
cd /path/to/libtwitcurl
g++ -c -I. twitcurl.cpp oauthlib.cpp urlencode.cpp base64.cpp HMAC_SHA1.cpp SHA1.cpp
ar rvs libtwitcurl.a *.o
```

Для полноценной работы программы необходимо указать пути к 4 файлам с токенами в twitApp.pro
```
CONSUMERKEY = "$$cat(/path/to/twitApp/ConsumerKey.txt)"
CONSUMERSECRET = "$$cat(/path/to/twitApp/ConsumerSecret.txt)"
ACCESSTOKENKEY = "$$cat(/path/to/twitApp/AccessTokenKey.txt)"
ACCESSTOKENSECRET = "$$cat(/path/to/twitApp/AccessTokenSecret.txt)"
```
