# Distributed-Lab-LR3
Було змінено реалізцію S-box. Від тепер вхідні дані розділяються на 2 тетради по 4 біти. Також функція приймає 2 значення. Перше - строка з якою будуть відбуватися маніпуляції, а друге - це булеве значення, якщо воно приймає значення true, то вхідна строка буде зашифрована, якщо false, то буде дешифровано.

Також функції шифрування та тести були рознесені по різним файлам, та виправлено дублікацію кода.

Для написання своїх тестів можна змінити значання у змінних str, str2, str3, які знаходяться на строках 328, 329, 330.

Результат виконання: 
Тест на вс? маленьк? л?тери
Вх?дна строка - qwertyuiopasdfghjklzxcvbnmйцукенгшщзхъфывапролджэячсмитьбю?їєё
Результат шифрування S-блоком -
╪ЩU◄AT"ж-ї☼?бЯ?(йi?T▬hЎО>%°ш>фl
Результат дешифрування S-блоком - qwertyuiopasdfghjklzxcvbnmйцукенгшщзхъфывапролджэячсмитьбю?їєё

Результат шифрування P-блоком - cщ9иё-№-}Ё)й8xy,lm<м┐iшh|=/ълn;?kRЇ{>оєпj*⌂Є~o:zїяы<>.к?+юЛЯО?
Результат дешифрування P-блоком - qwertyuiopasdfghjklzxcvbnmйцукенгшщзхъфывапролджэячсмитьбю?їєё

Тест на вс? Велик? л?тери
Вх?дна строка - QWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ?ЇЄё
Результат шифрування S-блоком - С[n Ль;"S?н RЦ?)?j→+,/гЭцft│?.a5Ж♥WH№%є?p<▼∟?Б?♫>Kич┼x↔7y┐l
Результат дешифрування S-блоком - QWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ?ЇЄё

Результат шифрування P-блоком - Ўс1а°?+%u !б0pq$de4д¤aр`t5'тгf37c│§s?ж?зb"wўvg2r·чу?6&в¶#цК_N?
Результат дешифрування P-блоком - QWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ?ЇЄё

Тест на цифри та спецсимволи
Вх?дна строка - 12345679~!@#$%^&*()_+-=|{}<>,.?/
Результат шифрування S-блоком - З#Г↑-♣?↕уэ      &6?Xче4?ПсШ'►!ял?q1u§
Результат дешифрування S-блоком - 12345679~!@#$%^&*()_+-=|{}<>,.?/

хM↔??н??Ь∟\Э]рування P-блоком - %ИЙ?TШЩ?ь        I↑↓фXL♀
Результат дешифрування P-блоком - 12345679~!@#$%^&*()_+-=|{}<>,.?/