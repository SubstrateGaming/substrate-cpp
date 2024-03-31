#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT babe
   {
   public:
      virtual ~babe() = default;

      /**
       * @brief Returns data about which slots (primary or secondary) can be claimed in the current epoch with the keys in the keystore
       * @warning This method is marked as unsafe.
       * @return HashMap<AuthorityId, EpochAuthorship>
       */
      virtual HashMap<AuthorityId, EpochAuthorship> babe_epochAuthorship() = 0;
   };
}
