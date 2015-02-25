<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
   <html>
   <head>
   </head>
   <body>
   <h3>Periodic table of elements</h3>
   <table border="1" cellspacing="5" cellpadding="5">
   <tr>
   <td align="center">Element name</td>
   <td align="center">Symbol</td>
   <td align="center">Atomic number</td>
   </tr>
   <xsl:apply-templates />
   </table>
   </body>
   </html>
</xsl:template>

<xsl:template match="//element">
   <tr>
   <td align="center"><xsl:value-of select="name" /></td>
   <td align="center"><xsl:value-of select="symbol" /></td>
   <td align="center"><xsl:value-of select="number" /></td>
   </tr>
</xsl:template>


</xsl:stylesheet>



