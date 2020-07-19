doc:
	pandoc README.md -o README.html --css pandoc.css --to html5 --highlight-style=haddock --self-contained 
