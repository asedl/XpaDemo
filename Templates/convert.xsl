<xsl:stylesheet version="1.0"
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" indent="yes"/>

<xsl:template match="/">
  <xsl:processing-instruction name="xml-stylesheet">type="text/xsl"
 href="style.xsl"</xsl:processing-instruction>
  <xsl:comment>Style sheet converted automatically to 
&lt;xsl:element&gt; syntax</xsl:comment>
  <xsl:apply-templates select="comment()"/>
  <xsl:apply-templates select="*"/>
</xsl:template>

<!-- Copy text, comments and processing instructions. -->
<xsl:template match="comment() | processing-instruction() | text()">
  <xsl:copy>
    <xsl:apply-templates />
  </xsl:copy>
</xsl:template>

<!-- Convert non-XSLT elements to <xsl:element> syntax. -->
<xsl:template match="*">
  <xsl:element name="xsl:element">
    <xsl:attribute name="name"><xsl:value-of select="name(.)"/></xsl:attribute>
    <xsl:apply-templates select="@*"/> <!-- Consolidate. -->
    <xsl:apply-templates select="node()"/>
  </xsl:element>
</xsl:template>

<!-- Convert non-XSLT attribute to <xsl:attribute> syntax. -->
<xsl:template match="@*">
  <xsl:element name="xsl:attribute">
    <xsl:attribute name="name"><xsl:value-of select="name(.)"/></xsl:attribute>
    <xsl:value-of select="."/>
  </xsl:element>
</xsl:template>

<!-- Copy namespace attributes. -->
<xsl:template match="@xmlns:*">
  <xsl:copy><xsl:value-of select="."/></xsl:copy>
</xsl:template>

<!-- Copy XSLT elements and their attributes. -->
<xsl:template match="xsl:*">
  <xsl:copy>
    <xsl:for-each select="@*">
      <xsl:copy><xsl:value-of select="."/></xsl:copy>
    </xsl:for-each>
    <xsl:apply-templates select="node()"/>
  </xsl:copy>
</xsl:template>

</xsl:stylesheet>