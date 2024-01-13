import requests
import re
from bs4 import BeautifulSoup


def scrape(name):
    url = "https://www.amd.com/de/direct-buy/at"
    site = requests.get(url)

    soup = BeautifulSoup(site.content, 'html.parser')
    divs = soup.find_all(class_='direct-buy')
    reTitle = re.compile('<div[^>]*class="shop-title"[^>]*>([^>]*)<\/div>')
    reShop = re.compile('<div[^>]*class="shop-links"[^>]*>([^>]*)<\/div>')

    for div in divs:
        if div.findAll(text=re.compile(name)):
            matches = re.search(reShop, str(div))
            nmatches = re.search(reTitle, str(div))
            if(matches and matches.group(1).lower().strip()!='out of stock'):
                print(nmatches.group(1).strip(), "available under: ", matches.group(1).strip())
            else:
                print(nmatches.group(1).strip(), "is not in stock.")

